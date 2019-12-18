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
 int ETH_ALEN ; 
 int char2hex (char) ; 
 char* prom_getenv (char*) ; 
 int /*<<< orphan*/  random_ether_addr (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char) ; 

__attribute__((used)) static void cpmac_get_mac(int instance, unsigned char *dev_addr)
{
	int i;
	char name[5], default_mac[ETH_ALEN], *mac;

	mac = NULL;
	sprintf(name, "mac%c", 'a' + instance);
	mac = prom_getenv(name);
	if (!mac) {
		sprintf(name, "mac%c", 'a');
		mac = prom_getenv(name);
	}
	if (!mac) {
		random_ether_addr(default_mac);
		mac = default_mac;
	}
	for (i = 0; i < 6; i++)
		dev_addr[i] = (char2hex(mac[i * 3]) << 4) +
			char2hex(mac[i * 3 + 1]);
}