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
 int /*<<< orphan*/  _ (char*) ; 
 char* desc_format ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*) ; 
 char* other_format ; 
 int print_radix ; 
 char* value_format_32bit ; 
 char* value_format_64bit ; 

__attribute__((used)) static void
set_print_radix (char *radix)
{
  switch (*radix)
    {
    case 'x':
      break;
    case 'd':
    case 'o':
      if (*radix == 'd')
	print_radix = 10;
      else
	print_radix = 8;
      value_format_32bit[4] = *radix;
      value_format_64bit[5] = *radix;
      other_format[3] = desc_format[3] = *radix;
      break;
    default:
      fatal (_("%s: invalid radix"), radix);
    }
}