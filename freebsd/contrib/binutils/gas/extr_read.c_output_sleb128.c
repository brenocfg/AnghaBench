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
typedef  int offsetT ;

/* Variables and functions */

__attribute__((used)) static inline int
output_sleb128 (char *p, offsetT value)
{
  register char *orig = p;
  register int more;

  do
    {
      unsigned byte = (value & 0x7f);

      /* Sadly, we cannot rely on typical arithmetic right shift behaviour.
	 Fortunately, we can structure things so that the extra work reduces
	 to a noop on systems that do things "properly".  */
      value = (value >> 7) | ~(-(offsetT)1 >> 7);

      more = !((((value == 0) && ((byte & 0x40) == 0))
		|| ((value == -1) && ((byte & 0x40) != 0))));
      if (more)
	byte |= 0x80;

      *p++ = byte;
    }
  while (more);

  return p - orig;
}