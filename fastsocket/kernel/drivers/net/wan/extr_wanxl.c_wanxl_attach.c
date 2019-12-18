#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  port_t ;
struct TYPE_2__ {unsigned short encoding; unsigned short parity; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned short ENCODING_NRZ ; 
 unsigned short ENCODING_NRZI ; 
 unsigned short PARITY_CRC16_PR0_CCITT ; 
 unsigned short PARITY_CRC16_PR1_CCITT ; 
 unsigned short PARITY_CRC32_PR0_CCITT ; 
 unsigned short PARITY_CRC32_PR1_CCITT ; 
 unsigned short PARITY_NONE ; 
 int /*<<< orphan*/ * dev_to_port (struct net_device*) ; 
 TYPE_1__* get_status (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wanxl_attach(struct net_device *dev, unsigned short encoding,
			unsigned short parity)
{
	port_t *port = dev_to_port(dev);

	if (encoding != ENCODING_NRZ &&
	    encoding != ENCODING_NRZI)
		return -EINVAL;

	if (parity != PARITY_NONE &&
	    parity != PARITY_CRC32_PR1_CCITT &&
	    parity != PARITY_CRC16_PR1_CCITT &&
	    parity != PARITY_CRC32_PR0_CCITT &&
	    parity != PARITY_CRC16_PR0_CCITT)
		return -EINVAL;

	get_status(port)->encoding = encoding;
	get_status(port)->parity = parity;
	return 0;
}