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
 int P1275_ARG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P1275_ARG_IN_BUF ; 
 int /*<<< orphan*/  P1275_ARG_IN_STRING ; 
 int P1275_INOUT (int,int) ; 
 int /*<<< orphan*/  P1275_SIZE (int) ; 
 scalar_t__ ldom_domaining_enabled ; 
 int /*<<< orphan*/  ldom_set_var (char const*,char*) ; 
 int p1275_cmd (char*,int,int,char const*,char*,int /*<<< orphan*/ ) ; 

int
prom_setprop(int node, const char *pname, char *value, int size)
{
	if (size == 0)
		return 0;
	if ((pname == 0) || (value == 0))
		return 0;
	
#ifdef CONFIG_SUN_LDOMS
	if (ldom_domaining_enabled) {
		ldom_set_var(pname, value);
		return 0;
	}
#endif
	return p1275_cmd ("setprop", P1275_ARG(1,P1275_ARG_IN_STRING)|
					  P1275_ARG(2,P1275_ARG_IN_BUF)|
					  P1275_INOUT(4, 1), 
					  node, pname, value, P1275_SIZE(size));
}