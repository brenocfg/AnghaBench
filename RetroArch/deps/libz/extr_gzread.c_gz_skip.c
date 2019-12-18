#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ z_off64_t ;
typedef  TYPE_3__* gz_statep ;
struct TYPE_6__ {scalar_t__ avail_in; } ;
struct TYPE_7__ {unsigned int have; unsigned int next; unsigned int pos; } ;
struct TYPE_8__ {TYPE_1__ strm; scalar_t__ eof; TYPE_2__ x; } ;

/* Variables and functions */
 scalar_t__ GT_OFF (unsigned int) ; 
 int gz_fetch (TYPE_3__*) ; 

__attribute__((used)) static int gz_skip(gz_statep state, z_off64_t len)
{
   unsigned n;

   /* skip over len bytes or reach end-of-file, whichever comes first */
   while (len)
      /* skip over whatever is in output buffer */
      if (state->x.have) {
         n = GT_OFF(state->x.have) || (z_off64_t)state->x.have > len ?
            (unsigned)len : state->x.have;
         state->x.have -= n;
         state->x.next += n;
         state->x.pos += n;
         len -= n;
      }

   /* output buffer empty -- return if we're at the end of the input */
      else if (state->eof && state->strm.avail_in == 0)
         break;

   /* need more data to skip -- load up output buffer */
      else {
         /* get more output, looking for header if required */
         if (gz_fetch(state) == -1)
            return -1;
      }
   return 0;
}