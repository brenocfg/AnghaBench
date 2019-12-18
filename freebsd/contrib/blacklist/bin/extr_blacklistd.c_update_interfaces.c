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
struct ifaddrs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 int getifaddrs (struct ifaddrs**) ; 
 struct ifaddrs* ifas ; 

__attribute__((used)) static void
update_interfaces(void)
{
	struct ifaddrs *oifas, *nifas;

	if (getifaddrs(&nifas) == -1)
		return;

	oifas = ifas;
	ifas = nifas;

	if (oifas)
		freeifaddrs(oifas);
}