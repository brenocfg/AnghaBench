#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct comp_unit {int addr_size; int /*<<< orphan*/  abfd; } ;
typedef  int /*<<< orphan*/  bfd_uint64_t ;
typedef  int /*<<< orphan*/  bfd_byte ;
struct TYPE_2__ {int sign_extend_vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bfd_get_16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_signed_16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_signed_32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_signed_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* get_elf_backend_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_uint64_t
read_address (struct comp_unit *unit, bfd_byte *buf)
{
  int signed_vma = get_elf_backend_data (unit->abfd)->sign_extend_vma;

  if (signed_vma)
    {
      switch (unit->addr_size)
	{
	case 8:
	  return bfd_get_signed_64 (unit->abfd, buf);
	case 4:
	  return bfd_get_signed_32 (unit->abfd, buf);
	case 2:
	  return bfd_get_signed_16 (unit->abfd, buf);
	default:
	  abort ();
	}
    }
  else
    {
      switch (unit->addr_size)
	{
	case 8:
	  return bfd_get_64 (unit->abfd, buf);
	case 4:
	  return bfd_get_32 (unit->abfd, buf);
	case 2:
	  return bfd_get_16 (unit->abfd, buf);
	default:
	  abort ();
	}
    }
}