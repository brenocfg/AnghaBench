#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* z_streamp ;
typedef  TYPE_3__* gz_statep ;
struct TYPE_8__ {unsigned int have; scalar_t__ next; } ;
struct TYPE_9__ {unsigned int avail_out; scalar_t__ avail_in; char* msg; scalar_t__ next_out; } ;
struct TYPE_10__ {int /*<<< orphan*/  how; TYPE_1__ x; TYPE_2__ strm; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOOK ; 
 int Z_BUF_ERROR ; 
 int Z_DATA_ERROR ; 
 int Z_MEM_ERROR ; 
 int Z_NEED_DICT ; 
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int Z_STREAM_ERROR ; 
 int gz_avail (TYPE_3__*) ; 
 int /*<<< orphan*/  gz_error (TYPE_3__*,int,char*) ; 
 int inflate (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gz_decomp(gz_statep state)
{
   int ret = Z_OK;
   unsigned had;
   z_streamp strm = &(state->strm);

   /* fill output buffer up to end of deflate stream */
   had = strm->avail_out;
   do {
      /* get more input for inflate() */
      if (strm->avail_in == 0 && gz_avail(state) == -1)
         return -1;
      if (strm->avail_in == 0) {
         gz_error(state, Z_BUF_ERROR, "unexpected end of file");
         break;
      }

      /* decompress and handle errors */
      ret = inflate(strm, Z_NO_FLUSH);
      if (ret == Z_STREAM_ERROR || ret == Z_NEED_DICT) {
         gz_error(state, Z_STREAM_ERROR,
               "internal error: inflate stream corrupt");
         return -1;
      }
      if (ret == Z_MEM_ERROR) {
         gz_error(state, Z_MEM_ERROR, "out of memory");
         return -1;
      }
      if (ret == Z_DATA_ERROR) {              /* deflate stream invalid */
         gz_error(state, Z_DATA_ERROR,
               strm->msg == NULL ? "compressed data error" : strm->msg);
         return -1;
      }
   } while (strm->avail_out && ret != Z_STREAM_END);

   /* update available output */
   state->x.have = had - strm->avail_out;
   state->x.next = strm->next_out - state->x.have;

   /* if the gzip stream completed successfully, look for another */
   if (ret == Z_STREAM_END)
      state->how = LOOK;

   /* good decompression */
   return 0;
}