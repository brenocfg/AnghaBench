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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 

u8
PlatformIORead1Byte(
	struct net_device *dev,
	u32		offset
	)
{
	u8	data = 0;

	data = read_nic_byte(dev, offset);


	return data;
}