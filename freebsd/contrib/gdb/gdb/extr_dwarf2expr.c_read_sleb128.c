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
typedef  unsigned char LONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 

unsigned char *
read_sleb128 (unsigned char *buf, unsigned char *buf_end, LONGEST * r)
{
  unsigned shift = 0;
  LONGEST result = 0;
  unsigned char byte;

  while (1)
    {
      if (buf >= buf_end)
	error ("read_sleb128: Corrupted DWARF expression.");

      byte = *buf++;
      result |= (byte & 0x7f) << shift;
      shift += 7;
      if ((byte & 0x80) == 0)
	break;
    }
  if (shift < (sizeof (*r) * 8) && (byte & 0x40) != 0)
    result |= -(1 << shift);

  *r = result;
  return buf;
}