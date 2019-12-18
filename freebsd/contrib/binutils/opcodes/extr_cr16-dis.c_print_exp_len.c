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

__attribute__((used)) static char *
print_exp_len (int size)
{
  switch (size)
    {
    case 4:
    case 5:
    case 6:
    case 8:
    case 14:
    case 16:
      return ":s";
    case 20:
    case 24:
    case 32:
      return ":m";
    case 48:
      return ":l";
    default:
      return "";
    }
}