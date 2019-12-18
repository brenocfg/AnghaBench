#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct iw_quality {int qual; int level; int noise; int /*<<< orphan*/  updated; } ;
typedef  int __u8 ;
struct TYPE_7__ {int /*<<< orphan*/  updated; } ;
struct TYPE_8__ {TYPE_2__ qual; } ;
struct TYPE_6__ {scalar_t__ FalseCcaUpperThreshold; } ;
struct TYPE_9__ {scalar_t__* BbpWriteLatch; TYPE_3__ iw_stats; TYPE_1__ BbpTuning; } ;
typedef  TYPE_4__* PRTMP_ADAPTER ;

/* Variables and functions */

__attribute__((used)) static void set_quality(PRTMP_ADAPTER pAdapter,
                        struct iw_quality *iq,
                        signed char rssi)
{
	__u8 ChannelQuality;

	// Normalize Rssi
	if (rssi >= -50)
        ChannelQuality = 100;
	else if (rssi >= -80) // between -50 ~ -80dbm
		ChannelQuality = (__u8)(24 + ((rssi + 80) * 26)/10);
	else if (rssi >= -90)   // between -80 ~ -90dbm
        ChannelQuality = (__u8)((rssi + 90) * 26)/10;
	else
		ChannelQuality = 0;

    iq->qual = (__u8)ChannelQuality;

    iq->level = (__u8)(rssi);
    iq->noise = (pAdapter->BbpWriteLatch[66] > pAdapter->BbpTuning.FalseCcaUpperThreshold) ? ((__u8)pAdapter->BbpTuning.FalseCcaUpperThreshold) : ((__u8) pAdapter->BbpWriteLatch[66]);		// noise level (dBm)
    iq->noise += 256 - 143;
    iq->updated = pAdapter->iw_stats.qual.updated;
}