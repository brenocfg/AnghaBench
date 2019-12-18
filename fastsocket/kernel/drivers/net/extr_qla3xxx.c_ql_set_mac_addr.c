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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {scalar_t__ dev_addr; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ql_set_mac_addr(struct net_device *ndev, u16 *addr)
{
	__le16 *p = (__le16 *)ndev->dev_addr;
	p[0] = cpu_to_le16(addr[0]);
	p[1] = cpu_to_le16(addr[1]);
	p[2] = cpu_to_le16(addr[2]);
}