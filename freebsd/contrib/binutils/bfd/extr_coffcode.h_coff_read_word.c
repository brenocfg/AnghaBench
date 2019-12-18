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
 int /*<<< orphan*/  TRUE ; 
 int bfd_bread (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int pelength ; 

__attribute__((used)) static bfd_boolean
coff_read_word (bfd *abfd, unsigned int *value)
{
  unsigned char b[2];
  int status;

  status = bfd_bread (b, (bfd_size_type) 2, abfd);
  if (status < 1)
    {
      *value = 0;
      return FALSE;
    }

  if (status == 1)
    *value = (unsigned int) b[0];
  else
    *value = (unsigned int) (b[0] + (b[1] << 8));

  pelength += (unsigned int) status;

  return TRUE;
}