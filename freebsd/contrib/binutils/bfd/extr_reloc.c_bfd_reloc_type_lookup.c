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
typedef  int /*<<< orphan*/  reloc_howto_type ;
typedef  int /*<<< orphan*/  bfd_reloc_code_real_type ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/ * BFD_SEND (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reloc_type_lookup ; 

reloc_howto_type *
bfd_reloc_type_lookup (bfd *abfd, bfd_reloc_code_real_type code)
{
  return BFD_SEND (abfd, reloc_type_lookup, (abfd, code));
}