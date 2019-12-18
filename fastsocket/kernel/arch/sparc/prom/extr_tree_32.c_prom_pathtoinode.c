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
 int /*<<< orphan*/  prom_devclose (int) ; 
 int prom_devopen (char*) ; 
 int prom_inst2pkg (int) ; 

int prom_pathtoinode(char *path)
{
	int node, inst;
	
	inst = prom_devopen (path);
	if (inst == -1) return 0;
	node = prom_inst2pkg (inst);
	prom_devclose (inst);
	if (node == -1) return 0;
	return node;
}