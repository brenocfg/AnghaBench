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
struct floatformat {int man_len; unsigned int man_start; int /*<<< orphan*/  totalsize; int /*<<< orphan*/  byteorder; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_assert (int) ; 
 unsigned long get_field (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

char *
floatformat_mantissa (const struct floatformat *fmt, char *val)
{
  unsigned char *uval = (unsigned char *) val;
  unsigned long mant;
  unsigned int mant_bits, mant_off;
  int mant_bits_left;
  static char res[50];
  char buf[9];

  /* Make sure we have enough room to store the mantissa.  */
  gdb_assert (fmt != NULL);
  gdb_assert (sizeof res > ((fmt->man_len + 7) / 8) * 2);

  mant_off = fmt->man_start;
  mant_bits_left = fmt->man_len;
  mant_bits = (mant_bits_left % 32) > 0 ? mant_bits_left % 32 : 32;

  mant = get_field (uval, fmt->byteorder, fmt->totalsize,
		    mant_off, mant_bits);

  sprintf (res, "%lx", mant);

  mant_off += mant_bits;
  mant_bits_left -= mant_bits;
  
  while (mant_bits_left > 0)
    {
      mant = get_field (uval, fmt->byteorder, fmt->totalsize,
			mant_off, 32);

      sprintf (buf, "%08lx", mant);
      strcat (res, buf);

      mant_off += 32;
      mant_bits_left -= 32;
    }

  return res;
}