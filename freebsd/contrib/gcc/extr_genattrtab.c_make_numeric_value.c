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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 int /*<<< orphan*/  CONST_STRING ; 
 int /*<<< orphan*/  MAX_DIGITS ; 
 char* attr_printf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ attr_rtx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static rtx
make_numeric_value (int n)
{
  static rtx int_values[20];
  rtx exp;
  char *p;

  gcc_assert (n >= 0);

  if (n < 20 && int_values[n])
    return int_values[n];

  p = attr_printf (MAX_DIGITS, "%d", n);
  exp = attr_rtx (CONST_STRING, p);

  if (n < 20)
    int_values[n] = exp;

  return exp;
}