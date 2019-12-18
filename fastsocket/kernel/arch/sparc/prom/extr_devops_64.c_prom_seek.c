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
 int /*<<< orphan*/  P1275_INOUT (int,int) ; 
 int /*<<< orphan*/  p1275_cmd (char*,int /*<<< orphan*/ ,int,unsigned int,unsigned int) ; 

void
prom_seek(int dhandle, unsigned int seekhi, unsigned int seeklo)
{
	p1275_cmd ("seek", P1275_INOUT(3,1), dhandle, seekhi, seeklo);
}