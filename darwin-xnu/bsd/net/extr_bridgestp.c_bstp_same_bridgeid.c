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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  PV2ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bstp_addr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bstp_same_bridgeid(uint64_t id1, uint64_t id2)
{
	u_char addr1[ETHER_ADDR_LEN];
	u_char addr2[ETHER_ADDR_LEN];

	PV2ADDR(id1, addr1);
	PV2ADDR(id2, addr2);

	if (bstp_addr_cmp(addr1, addr2) == 0)
		return (1);

	return (0);
}