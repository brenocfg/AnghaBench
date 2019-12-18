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
struct TYPE_2__ {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_over_errors; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 unsigned char SEEQ_RSTAT_CERROR ; 
 unsigned char SEEQ_RSTAT_DERROR ; 
 unsigned char SEEQ_RSTAT_OVERF ; 
 unsigned char SEEQ_RSTAT_REOF ; 
 unsigned char SEEQ_RSTAT_SFRAME ; 

__attribute__((used)) static void record_rx_errors(struct net_device *dev, unsigned char status)
{
	if (status & SEEQ_RSTAT_OVERF ||
	    status & SEEQ_RSTAT_SFRAME)
		dev->stats.rx_over_errors++;
	if (status & SEEQ_RSTAT_CERROR)
		dev->stats.rx_crc_errors++;
	if (status & SEEQ_RSTAT_DERROR)
		dev->stats.rx_frame_errors++;
	if (status & SEEQ_RSTAT_REOF)
		dev->stats.rx_errors++;
}