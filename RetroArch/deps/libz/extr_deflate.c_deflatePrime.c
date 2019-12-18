#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* z_streamp ;
typedef  int /*<<< orphan*/  ush ;
struct TYPE_7__ {int bi_valid; int /*<<< orphan*/  bi_buf; int /*<<< orphan*/ * pending_out; scalar_t__ d_buf; } ;
typedef  TYPE_2__ deflate_state ;
struct TYPE_6__ {struct TYPE_6__* state; } ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 int Buf_size ; 
 int Z_BUF_ERROR ; 
 TYPE_1__* Z_NULL ; 
 int Z_OK ; 
 int Z_STREAM_ERROR ; 
 int /*<<< orphan*/  _tr_flush_bits (TYPE_2__*) ; 

int deflatePrime (z_streamp strm, int bits, int value)
{
   deflate_state *s;
   int put;

   if (strm == Z_NULL || strm->state == Z_NULL) return Z_STREAM_ERROR;
   s = (deflate_state*)strm->state;
   if ((Bytef *)(s->d_buf) < s->pending_out + ((Buf_size + 7) >> 3))
      return Z_BUF_ERROR;
   do {
      put = Buf_size - s->bi_valid;
      if (put > bits)
         put = bits;
      s->bi_buf |= (ush)((value & ((1 << put) - 1)) << s->bi_valid);
      s->bi_valid += put;
      _tr_flush_bits(s);
      value >>= put;
      bits -= put;
   } while (bits);
   return Z_OK;
}