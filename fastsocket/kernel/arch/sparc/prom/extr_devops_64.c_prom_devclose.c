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
 int /*<<< orphan*/  P1275_INOUT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p1275_cmd (char*,int /*<<< orphan*/ ,int) ; 

int
prom_devclose(int dhandle)
{
	p1275_cmd ("close", P1275_INOUT(1,0), dhandle);
	return 0;
}