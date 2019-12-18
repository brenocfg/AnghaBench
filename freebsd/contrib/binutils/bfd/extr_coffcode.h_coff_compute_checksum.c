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
typedef  scalar_t__ file_ptr ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ coff_read_word (int /*<<< orphan*/ *,unsigned int*) ; 
 scalar_t__ pelength ; 

__attribute__((used)) static unsigned int
coff_compute_checksum (bfd *abfd)
{
  bfd_boolean more_data;
  file_ptr filepos;
  unsigned int value;
  unsigned int total;

  total = 0;
  pelength = 0;
  filepos = (file_ptr) 0;

  do
    {
      if (bfd_seek (abfd, filepos, SEEK_SET) != 0)
	return 0;

      more_data = coff_read_word (abfd, &value);
      total += value;
      total = 0xffff & (total + (total >> 0x10));
      filepos += 2;
    }
  while (more_data);

  return (0xffff & (total + (total >> 0x10)));
}