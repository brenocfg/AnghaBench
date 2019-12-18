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
 int EINVAL ; 
 unsigned short ENCODING_NRZ ; 
 unsigned short PARITY_CRC16_PR1_CCITT ; 

__attribute__((used)) static int cosa_net_attach(struct net_device *dev, unsigned short encoding,
			   unsigned short parity)
{
	if (encoding == ENCODING_NRZ && parity == PARITY_CRC16_PR1_CCITT)
		return 0;
	return -EINVAL;
}