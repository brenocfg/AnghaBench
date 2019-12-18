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
typedef  int png_uint_32 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int fgetc (int /*<<< orphan*/ *) ; 

png_uint_32 get_data (FILE *pnm_file, int depth)
{
  static int bits_left = 0;
  static int old_value = 0;
  static int mask = 0;
  int i;
  png_uint_32 ret_value;

  if (mask == 0)
    for (i = 0; i < depth; i++)
      mask = (mask >> 1) | 0x80;

  if (bits_left <= 0)
  {
    old_value = fgetc (pnm_file);
    bits_left = 8;
  }

  ret_value = old_value & mask;
  for (i = 1; i < (8 / depth); i++)
    ret_value = ret_value || (ret_value >> depth);

  old_value = (old_value << depth) & 0xFF;
  bits_left -= depth;

  return ret_value;
}