#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t state_out_pos; size_t numZ; TYPE_1__* strm; int /*<<< orphan*/ * zbits; } ;
struct TYPE_4__ {scalar_t__ avail_out; scalar_t__ total_out_lo32; int /*<<< orphan*/  total_out_hi32; int /*<<< orphan*/ * next_out; } ;
typedef  TYPE_2__ EState ;
typedef  scalar_t__ Bool ;

/* Variables and functions */
 scalar_t__ False ; 
 scalar_t__ True ; 

__attribute__((used)) static
Bool copy_output_until_stop ( EState* s )
{
   Bool progress_out = False;

   while (True) {

      /*-- no output space? --*/
      if (s->strm->avail_out == 0) break;

      /*-- block done? --*/
      if (s->state_out_pos >= s->numZ) break;

      progress_out = True;
      *(s->strm->next_out) = s->zbits[s->state_out_pos];
      s->state_out_pos++;
      s->strm->avail_out--;
      s->strm->next_out++;
      s->strm->total_out_lo32++;
      if (s->strm->total_out_lo32 == 0) s->strm->total_out_hi32++;
   }

   return progress_out;
}