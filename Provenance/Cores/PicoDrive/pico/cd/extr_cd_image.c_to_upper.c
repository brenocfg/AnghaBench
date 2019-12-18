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

__attribute__((used)) static void to_upper(char *d, const char *s)
{
  for (; *s != 0; d++, s++) {
    if ('a' <= *s && *s <= 'z')
      *d = *s - 'a' + 'A';
    else
      *d = *s;
  }
}