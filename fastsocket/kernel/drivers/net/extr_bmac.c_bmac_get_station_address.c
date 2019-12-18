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
 int EnetAddressOffset ; 
 int /*<<< orphan*/  SROMAddressBits ; 
 unsigned char bitrev8 (unsigned short) ; 
 unsigned short read_srom (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_and_select_srom (struct net_device*) ; 

__attribute__((used)) static void
bmac_get_station_address(struct net_device *dev, unsigned char *ea)
{
	int i;
	unsigned short data;

	for (i = 0; i < 6; i++)
		{
			reset_and_select_srom(dev);
			data = read_srom(dev, i + EnetAddressOffset/2, SROMAddressBits);
			ea[2*i]   = bitrev8(data & 0x0ff);
			ea[2*i+1] = bitrev8((data >> 8) & 0x0ff);
		}
}