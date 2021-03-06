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
struct ips_driver {int dummy; } ;

/* Variables and functions */
 int FSHIFT ; 
 int* avenrun ; 

__attribute__((used)) static bool ips_cpu_busy(struct ips_driver *ips)
{
	if ((avenrun[0] >> FSHIFT) > 1)
		return true;

	return false;
}