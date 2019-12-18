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
typedef  int u32 ;
struct pcap_chip {int /*<<< orphan*/  adc_mutex; } ;

/* Variables and functions */
 int PCAP_ADC_TS_M_MASK ; 
 int PCAP_ADC_TS_REF_LOWPWR ; 
 int /*<<< orphan*/  PCAP_REG_ADC ; 
 int /*<<< orphan*/  ezx_pcap_read (struct pcap_chip*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ezx_pcap_write (struct pcap_chip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void pcap_set_ts_bits(struct pcap_chip *pcap, u32 bits)
{
	u32 tmp;

	mutex_lock(&pcap->adc_mutex);
	ezx_pcap_read(pcap, PCAP_REG_ADC, &tmp);
	tmp &= ~(PCAP_ADC_TS_M_MASK | PCAP_ADC_TS_REF_LOWPWR);
	tmp |= bits & (PCAP_ADC_TS_M_MASK | PCAP_ADC_TS_REF_LOWPWR);
	ezx_pcap_write(pcap, PCAP_REG_ADC, tmp);
	mutex_unlock(&pcap->adc_mutex);
}