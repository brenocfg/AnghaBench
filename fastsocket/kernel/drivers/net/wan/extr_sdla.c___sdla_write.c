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
struct net_device {scalar_t__ mem_start; } ;

/* Variables and functions */
 int SDLA_ADDR_MASK ; 
 int /*<<< orphan*/  SDLA_WINDOW (struct net_device*,int) ; 
 int SDLA_WINDOW_SIZE ; 
 int /*<<< orphan*/  memcpy (void*,char const*,int) ; 

__attribute__((used)) static void __sdla_write(struct net_device *dev, int addr, 
			 const void *buf, short len)
{
	const char    *temp;
	void 	      *base;
	int           offset, bytes;

	temp = buf;
	while(len)
	{
		offset = addr & SDLA_ADDR_MASK;
		bytes = offset + len > SDLA_WINDOW_SIZE ? SDLA_WINDOW_SIZE - offset : len;
		base = (void *) (dev->mem_start + offset);

		SDLA_WINDOW(dev, addr);
		memcpy(base, temp, bytes);

		addr += bytes;
		temp += bytes;
		len  -= bytes;
	}
}