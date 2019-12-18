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
typedef  long valueT ;
struct TYPE_5__ {long fx_where; int fx_r_type; TYPE_1__* fx_frag; } ;
typedef  TYPE_2__ fixS ;
struct TYPE_4__ {long fr_address; } ;

/* Variables and functions */
#define  BFD_RELOC_23_PCREL_S2 130 
#define  BFD_RELOC_ALPHA_BRSGP 129 
#define  BFD_RELOC_ALPHA_HINT 128 

long
md_pcrel_from (fixS *fixP)
{
  valueT addr = fixP->fx_where + fixP->fx_frag->fr_address;

  switch (fixP->fx_r_type)
    {
    case BFD_RELOC_23_PCREL_S2:
    case BFD_RELOC_ALPHA_HINT:
    case BFD_RELOC_ALPHA_BRSGP:
      return addr + 4;
    default:
      return addr;
    }
}