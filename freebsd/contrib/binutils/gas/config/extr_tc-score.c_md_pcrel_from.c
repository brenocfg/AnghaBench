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
struct TYPE_5__ {long fx_where; TYPE_1__* fx_frag; int /*<<< orphan*/ * fx_subsy; scalar_t__ fx_addsy; } ;
typedef  TYPE_2__ fixS ;
struct TYPE_4__ {long fr_address; } ;

/* Variables and functions */
 scalar_t__ S_GET_SEGMENT (scalar_t__) ; 
 scalar_t__ undefined_section ; 

long
md_pcrel_from (fixS * fixP)
{
  long retval = 0;

  if (fixP->fx_addsy
      && (S_GET_SEGMENT (fixP->fx_addsy) == undefined_section)
      && (fixP->fx_subsy == NULL))
    {
      retval = 0;
    }
  else
    {
      retval = fixP->fx_where + fixP->fx_frag->fr_address;
    }

  return retval;
}