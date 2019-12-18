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
struct pcap_ts {int read_state; int /*<<< orphan*/  pcap; int /*<<< orphan*/  work; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int PCAP_ADC_TS_M_NONTS ; 
 int PCAP_ADC_TS_M_SHIFT ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct pcap_ts* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  pcap_set_ts_bits (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pcap_ts_close(struct input_dev *dev)
{
	struct pcap_ts *pcap_ts = input_get_drvdata(dev);

	cancel_delayed_work_sync(&pcap_ts->work);

	pcap_ts->read_state = PCAP_ADC_TS_M_NONTS;
	pcap_set_ts_bits(pcap_ts->pcap,
				pcap_ts->read_state << PCAP_ADC_TS_M_SHIFT);
}