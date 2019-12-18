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
typedef  int /*<<< orphan*/  bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_bwrite (unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 unsigned int coff_compute_checksum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  coff_read_word (int /*<<< orphan*/ *,int*) ; 
 int peheader ; 
 unsigned int pelength ; 

__attribute__((used)) static bfd_boolean
coff_apply_checksum (bfd *abfd)
{
  unsigned int computed;
  unsigned int checksum = 0;

  if (bfd_seek (abfd, 0x3c, SEEK_SET) != 0)
    return FALSE;

  if (!coff_read_word (abfd, &peheader))
    return FALSE;

  if (bfd_seek (abfd, peheader + 0x58, SEEK_SET) != 0)
    return FALSE;

  checksum = 0;
  bfd_bwrite (&checksum, (bfd_size_type) 4, abfd);

  if (bfd_seek (abfd, peheader, SEEK_SET) != 0)
    return FALSE;

  computed = coff_compute_checksum (abfd);

  checksum = computed + pelength;

  if (bfd_seek (abfd, peheader + 0x58, SEEK_SET) != 0)
    return FALSE;

  bfd_bwrite (&checksum, (bfd_size_type) 4, abfd);

  return TRUE;
}