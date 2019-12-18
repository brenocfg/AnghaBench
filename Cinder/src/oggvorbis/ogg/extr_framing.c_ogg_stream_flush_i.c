#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int lacing_fill; int b_o_s; int* lacing_vals; int* granule_vals; int* header; long serialno; int pageno; int header_fill; scalar_t__ body_returned; scalar_t__ body_data; scalar_t__ e_o_s; } ;
typedef  TYPE_1__ ogg_stream_state ;
struct TYPE_8__ {int* header; int header_len; int body_len; scalar_t__ body; } ;
typedef  TYPE_2__ ogg_page ;
typedef  int ogg_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,char*,int) ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 
 int /*<<< orphan*/  ogg_page_checksum_set (TYPE_2__*) ; 
 scalar_t__ ogg_stream_check (TYPE_1__*) ; 

__attribute__((used)) static int ogg_stream_flush_i(ogg_stream_state *os,ogg_page *og, int force, int nfill){
  int i;
  int vals=0;
  int maxvals=(os->lacing_fill>255?255:os->lacing_fill);
  int bytes=0;
  long acc=0;
  ogg_int64_t granule_pos=-1;

  if(ogg_stream_check(os)) return(0);
  if(maxvals==0) return(0);

  /* construct a page */
  /* decide how many segments to include */

  /* If this is the initial header case, the first page must only include
     the initial header packet */
  if(os->b_o_s==0){  /* 'initial header page' case */
    granule_pos=0;
    for(vals=0;vals<maxvals;vals++){
      if((os->lacing_vals[vals]&0x0ff)<255){
        vals++;
        break;
      }
    }
  }else{

    /* The extra packets_done, packet_just_done logic here attempts to do two things:
       1) Don't unneccessarily span pages.
       2) Unless necessary, don't flush pages if there are less than four packets on
          them; this expands page size to reduce unneccessary overhead if incoming packets
          are large.
       These are not necessary behaviors, just 'always better than naive flushing'
       without requiring an application to explicitly request a specific optimized
       behavior. We'll want an explicit behavior setup pathway eventually as well. */

    int packets_done=0;
    int packet_just_done=0;
    for(vals=0;vals<maxvals;vals++){
      if(acc>nfill && packet_just_done>=4){
        force=1;
        break;
      }
      acc+=os->lacing_vals[vals]&0x0ff;
      if((os->lacing_vals[vals]&0xff)<255){
        granule_pos=os->granule_vals[vals];
        packet_just_done=++packets_done;
      }else
        packet_just_done=0;
    }
    if(vals==255)force=1;
  }

  if(!force) return(0);

  /* construct the header in temp storage */
  memcpy(os->header,"OggS",4);

  /* stream structure version */
  os->header[4]=0x00;

  /* continued packet flag? */
  os->header[5]=0x00;
  if((os->lacing_vals[0]&0x100)==0)os->header[5]|=0x01;
  /* first page flag? */
  if(os->b_o_s==0)os->header[5]|=0x02;
  /* last page flag? */
  if(os->e_o_s && os->lacing_fill==vals)os->header[5]|=0x04;
  os->b_o_s=1;

  /* 64 bits of PCM position */
  for(i=6;i<14;i++){
    os->header[i]=(unsigned char)(granule_pos&0xff);
    granule_pos>>=8;
  }

  /* 32 bits of stream serial number */
  {
    long serialno=os->serialno;
    for(i=14;i<18;i++){
      os->header[i]=(unsigned char)(serialno&0xff);
      serialno>>=8;
    }
  }

  /* 32 bits of page counter (we have both counter and page header
     because this val can roll over) */
  if(os->pageno==-1)os->pageno=0; /* because someone called
                                     stream_reset; this would be a
                                     strange thing to do in an
                                     encode stream, but it has
                                     plausible uses */
  {
    long pageno=os->pageno++;
    for(i=18;i<22;i++){
      os->header[i]=(unsigned char)(pageno&0xff);
      pageno>>=8;
    }
  }

  /* zero for computation; filled in later */
  os->header[22]=0;
  os->header[23]=0;
  os->header[24]=0;
  os->header[25]=0;

  /* segment table */
  os->header[26]=(unsigned char)(vals&0xff);
  for(i=0;i<vals;i++)
    bytes+=os->header[i+27]=(unsigned char)(os->lacing_vals[i]&0xff);

  /* set pointers in the ogg_page struct */
  og->header=os->header;
  og->header_len=os->header_fill=vals+27;
  og->body=os->body_data+os->body_returned;
  og->body_len=bytes;

  /* advance the lacing data and set the body_returned pointer */

  os->lacing_fill-=vals;
  memmove(os->lacing_vals,os->lacing_vals+vals,os->lacing_fill*sizeof(*os->lacing_vals));
  memmove(os->granule_vals,os->granule_vals+vals,os->lacing_fill*sizeof(*os->granule_vals));
  os->body_returned+=bytes;

  /* calculate the checksum */

  ogg_page_checksum_set(og);

  /* done */
  return(1);
}