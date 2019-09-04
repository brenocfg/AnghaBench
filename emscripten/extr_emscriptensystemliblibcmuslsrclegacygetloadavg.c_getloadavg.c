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
struct sysinfo {double* loads; } ;

/* Variables and functions */
 int SI_LOAD_SHIFT ; 
 int /*<<< orphan*/  sysinfo (struct sysinfo*) ; 

int getloadavg(double *a, int n)
{
	struct sysinfo si;
	if (n <= 0) return n ? -1 : 0;
	sysinfo(&si);
	if (n > 3) n = 3;
	for (int i=0; i<n; i++)
		a[i] = 1.0/(1<<SI_LOAD_SHIFT) * si.loads[i];
	return n;
}