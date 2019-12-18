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
 int /*<<< orphan*/  P1275_ARG_IN_STRING ; 
 int /*<<< orphan*/  P1275_ARG_OUT_BUF ; 
 int P1275_INOUT (int,int) ; 
 int /*<<< orphan*/  P1275_SIZE (int) ; 
 int p1275_cmd (int /*<<< orphan*/ ,int,int,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prom_getprop_name ; 
 int prom_getproplen (int,char const*) ; 

inline int prom_getproperty(int node, const char *prop,
			    char *buffer, int bufsize)
{
	int plen;

	plen = prom_getproplen(node, prop);
	if ((plen > bufsize) || (plen == 0) || (plen == -1)) {
		return -1;
	} else {
		/* Ok, things seem all right. */
		return p1275_cmd(prom_getprop_name, 
				 P1275_ARG(1,P1275_ARG_IN_STRING)|
				 P1275_ARG(2,P1275_ARG_OUT_BUF)|
				 P1275_INOUT(4, 1), 
				 node, prop, buffer, P1275_SIZE(plen));
	}
}