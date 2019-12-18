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
struct TYPE_5__ {TYPE_1__* dyn_ltree; } ;
typedef  TYPE_2__ deflate_state ;
struct TYPE_4__ {scalar_t__ Freq; } ;

/* Variables and functions */
 int LITERALS ; 
 int Z_BINARY ; 
 int Z_TEXT ; 

__attribute__((used)) static int detect_data_type(deflate_state *s)
   {
      /* black_mask is the bit mask of black-listed bytes
       * set bits 0..6, 14..25, and 28..31
       * 0xf3ffc07f = binary 11110011111111111100000001111111
       */
      unsigned long black_mask = 0xf3ffc07fUL;
      int n;

      /* Check for non-textual ("black-listed") bytes. */
      for (n = 0; n <= 31; n++, black_mask >>= 1)
         if ((black_mask & 1) && (s->dyn_ltree[n].Freq != 0))
            return Z_BINARY;

      /* Check for textual ("white-listed") bytes. */
      if (s->dyn_ltree[9].Freq != 0 || s->dyn_ltree[10].Freq != 0
            || s->dyn_ltree[13].Freq != 0)
         return Z_TEXT;
      for (n = 32; n < LITERALS; n++)
         if (s->dyn_ltree[n].Freq != 0)
            return Z_TEXT;

      /* There are no "black-listed" or "white-listed" bytes:
       * this stream either is empty or has tolerated ("gray-listed") bytes only.
       */
      return Z_BINARY;
   }