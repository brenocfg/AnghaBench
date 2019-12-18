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
typedef  int /*<<< orphan*/  symbolS ;
typedef  scalar_t__ addressT ;

/* Variables and functions */
 int /*<<< orphan*/  TC_IMPLICIT_LCOMM_ALIGNMENT (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bss_alloc (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ parse_align (int) ; 

symbolS *
s_lcomm_internal (int needs_align, symbolS *symbolP, addressT size)
{
  addressT align = 0;

  if (needs_align)
    {
      align = parse_align (needs_align - 1);
      if (align == (addressT) -1)
	return NULL;
    }
  else
    /* Assume some objects may require alignment on some systems.  */
    TC_IMPLICIT_LCOMM_ALIGNMENT (size, align);

  bss_alloc (symbolP, size, align);
  return symbolP;
}