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
typedef  int u8 ;
struct net_device {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_IEEE802154 ; 
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static u8 fake_get_dsn(struct net_device *dev)
{
	BUG_ON(dev->type != ARPHRD_IEEE802154);

	return 0x00; /* DSN are implemented in HW, so return just 0 */
}