#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* z_streamp ;
struct TYPE_9__ {int wrap; int /*<<< orphan*/  last_flush; int /*<<< orphan*/  status; int /*<<< orphan*/  pending_buf; int /*<<< orphan*/  pending_out; scalar_t__ pending; } ;
typedef  TYPE_2__ deflate_state ;
struct TYPE_8__ {int /*<<< orphan*/  adler; struct TYPE_8__* state; int /*<<< orphan*/  data_type; struct TYPE_8__* msg; scalar_t__ total_out; scalar_t__ total_in; struct TYPE_8__* zfree; struct TYPE_8__* zalloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUSY_STATE ; 
 int /*<<< orphan*/  INIT_STATE ; 
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 TYPE_1__* Z_NULL ; 
 int Z_OK ; 
 int Z_STREAM_ERROR ; 
 int /*<<< orphan*/  Z_UNKNOWN ; 
 int /*<<< orphan*/  _tr_init (TYPE_2__*) ; 
 int /*<<< orphan*/  adler32 (long,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crc32 (long,TYPE_1__*,int /*<<< orphan*/ ) ; 

int deflateResetKeep (z_streamp strm)
{
   deflate_state *s;

   if (strm == Z_NULL || strm->state == Z_NULL ||
         strm->zalloc == Z_NULL || strm->zfree == Z_NULL) {
      return Z_STREAM_ERROR;
   }

   strm->total_in = strm->total_out = 0;
   strm->msg = Z_NULL; /* use zfree if we ever allocate msg dynamically */
   strm->data_type = Z_UNKNOWN;

   s = (deflate_state *)strm->state;
   s->pending = 0;
   s->pending_out = s->pending_buf;

   if (s->wrap < 0) {
      s->wrap = -s->wrap; /* was made negative by deflate(..., Z_FINISH); */
   }
   s->status = s->wrap ? INIT_STATE : BUSY_STATE;
   strm->adler =
#ifdef GZIP
      s->wrap == 2 ? crc32(0L, Z_NULL, 0) :
#endif
      adler32(0L, Z_NULL, 0);
   s->last_flush = Z_NO_FLUSH;

   _tr_init(s);

   return Z_OK;
}