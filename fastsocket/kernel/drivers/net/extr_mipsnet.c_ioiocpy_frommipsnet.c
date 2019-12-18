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
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regaddr (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxDataBuffer ; 
 int /*<<< orphan*/  rxDataCount ; 

__attribute__((used)) static int ioiocpy_frommipsnet(struct net_device *dev, unsigned char *kdata,
			int len)
{
	for (; len > 0; len--, kdata++)
		*kdata = inb(regaddr(dev, rxDataBuffer));

	return inl(regaddr(dev, rxDataCount));
}