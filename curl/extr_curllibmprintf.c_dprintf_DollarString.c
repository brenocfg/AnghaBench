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
 scalar_t__ ISDIGIT (char) ; 

__attribute__((used)) static long dprintf_DollarString(char *input, char **end)
{
  int number = 0;
  while(ISDIGIT(*input)) {
    number *= 10;
    number += *input-'0';
    input++;
  }
  if(number && ('$'==*input++)) {
    *end = input;
    return number;
  }
  return 0;
}