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
typedef  int /*<<< orphan*/  RTX_CODE ;

/* Variables and functions */
 char* GET_RTX_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOUPPER (char const) ; 
 int /*<<< orphan*/  putchar (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_code (RTX_CODE code)
{
  const char *p1;
  for (p1 = GET_RTX_NAME (code); *p1; p1++)
    putchar (TOUPPER(*p1));
}