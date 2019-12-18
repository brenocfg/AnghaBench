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
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int ULONGEST ;
typedef  int LONGEST ;

/* Variables and functions */
 int bfd_get_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bfd_get_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ULONGEST
read_initial_length (bfd *abfd, char *buf, unsigned int *bytes_read_ptr)
{
  LONGEST result;

  result = bfd_get_32 (abfd, (bfd_byte *) buf);
  if (result == 0xffffffff)
    {
      result = bfd_get_64 (abfd, (bfd_byte *) buf + 4);
      *bytes_read_ptr = 12;
    }
  else
    *bytes_read_ptr = 4;

  return result;
}