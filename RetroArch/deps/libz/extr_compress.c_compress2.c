#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ total_out; scalar_t__ opaque; void* zfree; void* zalloc; void* avail_out; int /*<<< orphan*/ * next_out; void* avail_in; int /*<<< orphan*/ * next_in; } ;
typedef  TYPE_1__ z_stream ;
typedef  scalar_t__ voidpf ;
typedef  scalar_t__ uLongf ;
typedef  scalar_t__ uLong ;
typedef  void* uInt ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 int Z_BUF_ERROR ; 
 int /*<<< orphan*/  Z_FINISH ; 
 void* Z_NULL ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int deflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int deflateEnd (TYPE_1__*) ; 
 int deflateInit (TYPE_1__*,int) ; 

int compress2 (Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen, int level)
{
   z_stream stream;
   int err;

   stream.next_in = (Bytef *)source;
   stream.avail_in = (uInt)sourceLen;
#ifdef MAXSEG_64K
   /* Check for source > 64K on 16-bit machine: */
   if ((uLong)stream.avail_in != sourceLen) return Z_BUF_ERROR;
#endif
   stream.next_out = dest;
   stream.avail_out = (uInt)*destLen;
   if ((uLong)stream.avail_out != *destLen) return Z_BUF_ERROR;

   stream.zalloc = Z_NULL;
   stream.zfree = Z_NULL;
   stream.opaque = (voidpf)0;

   err = deflateInit(&stream, level);
   if (err != Z_OK) return err;

   err = deflate(&stream, Z_FINISH);
   if (err != Z_STREAM_END) {
      deflateEnd(&stream);
      return err == Z_OK ? Z_BUF_ERROR : err;
   }
   *destLen = stream.total_out;

   err = deflateEnd(&stream);
   return err;
}