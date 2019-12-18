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
typedef  unsigned char u16 ;
struct niu {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMAC_ADDR0 ; 
 int /*<<< orphan*/  BMAC_ADDR1 ; 
 int /*<<< orphan*/  BMAC_ADDR2 ; 
 int NIU_FLAGS_XMAC ; 
 int /*<<< orphan*/  XMAC_ADDR0 ; 
 int /*<<< orphan*/  XMAC_ADDR1 ; 
 int /*<<< orphan*/  XMAC_ADDR2 ; 
 int /*<<< orphan*/  nw64_mac (int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void niu_set_primary_mac(struct niu *np, unsigned char *addr)
{
	u16 reg0 = addr[4] << 8 | addr[5];
	u16 reg1 = addr[2] << 8 | addr[3];
	u16 reg2 = addr[0] << 8 | addr[1];

	if (np->flags & NIU_FLAGS_XMAC) {
		nw64_mac(XMAC_ADDR0, reg0);
		nw64_mac(XMAC_ADDR1, reg1);
		nw64_mac(XMAC_ADDR2, reg2);
	} else {
		nw64_mac(BMAC_ADDR0, reg0);
		nw64_mac(BMAC_ADDR1, reg1);
		nw64_mac(BMAC_ADDR2, reg2);
	}
}