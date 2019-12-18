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

/* Variables and functions */
 unsigned char bfd_get_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static long
read_signed_leb128 (bfd *abfd, char *buf, unsigned int *bytes_read_ptr)
{
  long result;
  int i, shift, size, num_read;
  unsigned char byte;

  result = 0;
  shift = 0;
  size = 32;
  num_read = 0;
  i = 0;
  while (1)
    {
      byte = bfd_get_8 (abfd, (bfd_byte *) buf);
      buf++;
      num_read++;
      result |= ((long)(byte & 127) << shift);
      shift += 7;
      if ((byte & 128) == 0)
	{
	  break;
	}
    }
  if ((shift < size) && (byte & 0x40))
    {
      result |= -(1 << shift);
    }
  *bytes_read_ptr = num_read;
  return result;
}