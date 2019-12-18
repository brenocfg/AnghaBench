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
 scalar_t__ isdigit (unsigned char) ; 

__attribute__((used)) static int getint(const char **string)
{
  int i = 0;

  while (isdigit((unsigned char)**string) != 0) {
    i = i * 10 + (**string - '0');
    (*string)++;
  }

  if (i < 0 || i > 32767)
    i = 32767; /* if we have i==-10 this is not because the number is */
  /* negative; this is because the number is big */
  return i;
}