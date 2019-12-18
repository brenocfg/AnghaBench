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
typedef  unsigned char ULONGEST ;

/* Variables and functions */
 unsigned char bfd_get_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ULONGEST
read_unsigned_leb128 (bfd *abfd, char *buf, unsigned int *bytes_read_ptr)
{
  ULONGEST result;
  unsigned int num_read;
  int shift;
  unsigned char byte;

  result = 0;
  shift = 0;
  num_read = 0;

  do
    {
      byte = bfd_get_8 (abfd, (bfd_byte *) buf);
      buf++;
      num_read++;
      result |= ((byte & 0x7f) << shift);
      shift += 7;
    }
  while (byte & 0x80);

  *bytes_read_ptr = num_read;

  return result;
}