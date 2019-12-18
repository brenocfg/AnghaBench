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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ ISSPACE (char const) ; 
 char* XSTR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_bypass_1 (char const*,int) ; 

__attribute__((used)) static void
gen_bypass (rtx def)
{
  const char *p, *base;

  for (p = base = XSTR (def, 1); *p; p++)
    if (*p == ',')
      {
	gen_bypass_1 (base, p - base);
	do
	  p++;
	while (ISSPACE (*p));
	base = p;
      }
  gen_bypass_1 (base, p - base);
}