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
struct mv643xx_eth_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_ADDR_HIGH ; 
 int /*<<< orphan*/  MAC_ADDR_LOW ; 
 unsigned int rdlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uc_addr_get(struct mv643xx_eth_private *mp, unsigned char *addr)
{
	unsigned int mac_h = rdlp(mp, MAC_ADDR_HIGH);
	unsigned int mac_l = rdlp(mp, MAC_ADDR_LOW);

	addr[0] = (mac_h >> 24) & 0xff;
	addr[1] = (mac_h >> 16) & 0xff;
	addr[2] = (mac_h >> 8) & 0xff;
	addr[3] = mac_h & 0xff;
	addr[4] = (mac_l >> 8) & 0xff;
	addr[5] = mac_l & 0xff;
}