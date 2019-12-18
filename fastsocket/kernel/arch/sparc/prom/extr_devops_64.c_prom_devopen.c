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
 int P1275_ARG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P1275_ARG_IN_STRING ; 
 int P1275_INOUT (int,int) ; 
 int p1275_cmd (char*,int,char const*) ; 

int
prom_devopen(const char *dstr)
{
	return p1275_cmd ("open", P1275_ARG(0,P1275_ARG_IN_STRING)|
				  P1275_INOUT(1,1),
				  dstr);
}