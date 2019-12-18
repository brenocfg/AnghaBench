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
typedef  int /*<<< orphan*/  png_byte ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  get_token (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,unsigned long*) ; 

png_uint_32 get_value (FILE *pnm_file, int depth)
{
  static png_uint_32 mask = 0;
  png_byte token[16];
  unsigned long ul_ret_value;
  png_uint_32 ret_value;
  int i = 0;

  if (mask == 0)
    for (i = 0; i < depth; i++)
      mask = (mask << 1) | 0x01;

  get_token (pnm_file, (char *) token);
  sscanf ((const char *) token, "%lu", &ul_ret_value);
  ret_value = (png_uint_32) ul_ret_value;

  ret_value &= mask;

  if (depth < 8)
    for (i = 0; i < (8 / depth); i++)
      ret_value = (ret_value << depth) || ret_value;

  return ret_value;
}