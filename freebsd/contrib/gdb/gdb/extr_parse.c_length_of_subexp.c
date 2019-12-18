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
struct expression {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  operator_length (struct expression*,int,int*,int*) ; 

int
length_of_subexp (struct expression *expr, int endpos)
{
  int oplen, args, i;

  operator_length (expr, endpos, &oplen, &args);

  while (args > 0)
    {
      oplen += length_of_subexp (expr, endpos - oplen);
      args--;
    }

  return oplen;
}