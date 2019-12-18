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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct aggTally {scalar_t__ time; scalar_t__ avg_sent_bytes; scalar_t__ avg_sent_packets; scalar_t__ avg_got_bytes; scalar_t__ avg_got_packets; scalar_t__ sent_packets_sum; scalar_t__ sent_bytes_sum; scalar_t__ got_bytes_sum; scalar_t__ got_packets_sum; } ;
struct TYPE_2__ {struct aggTally agg_tal; } ;

/* Variables and functions */
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u16_t zfAggTallyReset(zdev_t* dev)
{
    struct aggTally* agg_tal;

    zmw_get_wlan_dev(dev);

    //zmw_declare_for_critical_section();

    agg_tal = &wd->agg_tal;
    agg_tal->got_packets_sum = 0;
    agg_tal->got_bytes_sum = 0;
    agg_tal->sent_bytes_sum = 0;
    agg_tal->sent_packets_sum = 0;
    agg_tal->avg_got_packets = 0;
    agg_tal->avg_got_bytes = 0;
    agg_tal->avg_sent_packets = 0;
    agg_tal->avg_sent_bytes = 0;
    agg_tal->time = 0;
    return 0;
}