#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ type; int /*<<< orphan*/  file; TYPE_3__* param; } ;
typedef  TYPE_2__ pm_file ;
typedef  TYPE_3__* gzFile ;
struct TYPE_9__ {int align; } ;
struct TYPE_11__ {int fpos_out; int* index; unsigned char* out_buff; int fpos_in; int block_in_buff; unsigned char* in_buff; TYPE_1__ header; } ;
typedef  TYPE_3__ cso_struct ;

/* Variables and functions */
 int /*<<< orphan*/  EL_STATUS ; 
 scalar_t__ PMT_CSO ; 
 scalar_t__ PMT_UNCOMPRESSED ; 
 scalar_t__ PMT_ZIP ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int Z_DATA_ERROR ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int fread (unsigned char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int gzerror2 (TYPE_3__*) ; 
 int gzread (TYPE_3__*,void*,size_t) ; 
 int /*<<< orphan*/  gzrewind (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int uncompress2 (unsigned char*,int,unsigned char*,int) ; 

size_t pm_read(void *ptr, size_t bytes, pm_file *stream)
{
  int ret;

  if (stream->type == PMT_UNCOMPRESSED)
  {
    ret = fread(ptr, 1, bytes, stream->file);
  }
  else if (stream->type == PMT_ZIP)
  {
    gzFile gf = stream->param;
    int err;
    ret = gzread(gf, ptr, bytes);
    err = gzerror2(gf);
    if (ret > 0 && (err == Z_DATA_ERROR || err == Z_STREAM_END))
      /* we must reset stream pointer or else next seek/read fails */
      gzrewind(gf);
  }
  else if (stream->type == PMT_CSO)
  {
    cso_struct *cso = stream->param;
    int read_pos, read_len, out_offs, rret;
    int block = cso->fpos_out >> 11;
    int index = cso->index[block];
    int index_end = cso->index[block+1];
    unsigned char *out = ptr, *tmp_dst;

    ret = 0;
    while (bytes != 0)
    {
      out_offs = cso->fpos_out&0x7ff;
      if (out_offs == 0 && bytes >= 2048)
           tmp_dst = out;
      else tmp_dst = cso->out_buff;

      read_pos = (index&0x7fffffff) << cso->header.align;

      if (index < 0) {
        if (read_pos != cso->fpos_in)
          fseek(stream->file, read_pos, SEEK_SET);
        rret = fread(tmp_dst, 1, 2048, stream->file);
        cso->fpos_in = read_pos + rret;
        if (rret != 2048) break;
      } else {
        read_len = (((index_end&0x7fffffff) << cso->header.align) - read_pos) & 0xfff;
        if (block != cso->block_in_buff)
        {
          if (read_pos != cso->fpos_in)
            fseek(stream->file, read_pos, SEEK_SET);
          rret = fread(cso->in_buff, 1, read_len, stream->file);
          cso->fpos_in = read_pos + rret;
          if (rret != read_len) {
            elprintf(EL_STATUS, "cso: read failed @ %08x", read_pos);
            break;
          }
          cso->block_in_buff = block;
        }
        rret = uncompress2(tmp_dst, 2048, cso->in_buff, read_len);
        if (rret != 0) {
          elprintf(EL_STATUS, "cso: uncompress failed @ %08x with %i", read_pos, rret);
          break;
        }
      }

      rret = 2048;
      if (out_offs != 0 || bytes < 2048) {
        //elprintf(EL_STATUS, "cso: unaligned/nonfull @ %08x, offs=%i, len=%u", cso->fpos_out, out_offs, bytes);
        if (bytes < rret) rret = bytes;
        if (2048 - out_offs < rret) rret = 2048 - out_offs;
        memcpy(out, tmp_dst + out_offs, rret);
      }
      ret += rret;
      out += rret;
      cso->fpos_out += rret;
      bytes -= rret;
      block++;
      index = index_end;
      index_end = cso->index[block+1];
    }
  }
  else
    ret = 0;

  return ret;
}