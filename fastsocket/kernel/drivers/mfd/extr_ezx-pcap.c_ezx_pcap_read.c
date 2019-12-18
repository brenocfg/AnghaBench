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
typedef  int u32 ;
struct pcap_chip {int /*<<< orphan*/  io_mutex; } ;

/* Variables and functions */
 int PCAP_REGISTER_ADDRESS_SHIFT ; 
 int PCAP_REGISTER_READ_OP_BIT ; 
 int ezx_pcap_putget (struct pcap_chip*,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ezx_pcap_read(struct pcap_chip *pcap, u8 reg_num, u32 *value)
{
	int ret;

	mutex_lock(&pcap->io_mutex);
	*value = PCAP_REGISTER_READ_OP_BIT
		| (reg_num << PCAP_REGISTER_ADDRESS_SHIFT);

	ret = ezx_pcap_putget(pcap, value);
	mutex_unlock(&pcap->io_mutex);

	return ret;
}