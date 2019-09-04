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

/* Variables and functions */

int number_of_characters_in_utf8_string(const char *str)
{
  if (!str) return 0;
  int num_chars = 0;
  while(*str)
  {
    if ((*str++ & 0xC0) != 0x80) ++num_chars; // Skip all continuation bytes
  }
  return num_chars;
}