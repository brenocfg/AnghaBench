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
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
#define  C_EXT 129 
#define  C_WEAKEXT 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static bfd_boolean
external_coff_symbol_p (int sym_class)
{
  switch (sym_class)
    {
    case C_EXT:
    case C_WEAKEXT:
      return TRUE;
    default:
      break;
    }
  return FALSE;
}