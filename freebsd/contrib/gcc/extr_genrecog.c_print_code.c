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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
 char* GET_RTX_NAME (int) ; 
 int /*<<< orphan*/  TOUPPER (char const) ; 
 int /*<<< orphan*/  putchar (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_code (enum rtx_code code)
{
  const char *p;
  for (p = GET_RTX_NAME (code); *p; p++)
    putchar (TOUPPER (*p));
}