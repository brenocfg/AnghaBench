#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int relax_addressT ;

/* Variables and functions */
 scalar_t__ linkrelax ; 

__attribute__((used)) static relax_addressT
relax_align (register relax_addressT address,	/* Address now.  */
	     register int alignment	/* Alignment (binary).  */)
{
  relax_addressT mask;
  relax_addressT new_address;

  mask = ~((~0) << alignment);
  new_address = (address + mask) & (~mask);
#ifdef LINKER_RELAXING_SHRINKS_ONLY
  if (linkrelax)
    /* We must provide lots of padding, so the linker can discard it
       when needed.  The linker will not add extra space, ever.  */
    new_address += (1 << alignment);
#endif
  return (new_address - address);
}