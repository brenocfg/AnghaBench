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
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_FAIL () ; 
 int /*<<< orphan*/  bfd_get_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_signed_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_signed_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_signed_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_vma
read_value (bfd *abfd, bfd_byte *buf, int width, int is_signed)
{
  bfd_vma value;

  switch (width)
    {
    case 2:
      if (is_signed)
	value = bfd_get_signed_16 (abfd, buf);
      else
	value = bfd_get_16 (abfd, buf);
      break;
    case 4:
      if (is_signed)
	value = bfd_get_signed_32 (abfd, buf);
      else
	value = bfd_get_32 (abfd, buf);
      break;
    case 8:
      if (is_signed)
	value = bfd_get_signed_64 (abfd, buf);
      else
	value = bfd_get_64 (abfd, buf);
      break;
    default:
      BFD_FAIL ();
      return 0;
    }

  return value;
}