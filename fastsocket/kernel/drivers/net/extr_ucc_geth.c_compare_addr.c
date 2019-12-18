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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_NUM_OCTETS_PER_ADDRESS ; 
 int memcmp (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int compare_addr(u8 **addr1, u8 **addr2)
{
	return memcmp(addr1, addr2, ENET_NUM_OCTETS_PER_ADDRESS);
}