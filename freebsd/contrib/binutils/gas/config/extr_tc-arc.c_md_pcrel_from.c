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
struct TYPE_5__ {long fx_where; long fx_size; TYPE_1__* fx_frag; } ;
typedef  TYPE_2__ fixS ;
struct TYPE_4__ {long fr_address; } ;

/* Variables and functions */

long
md_pcrel_from (fixS *fixP)
{
  /* Return the address of the delay slot.  */
  return fixP->fx_frag->fr_address + fixP->fx_where + fixP->fx_size;
}