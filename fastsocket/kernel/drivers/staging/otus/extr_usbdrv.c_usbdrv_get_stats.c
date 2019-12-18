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
struct net_device_stats {scalar_t__ rx_length_errors; scalar_t__ rx_frame_errors; scalar_t__ rx_crc_errors; scalar_t__ rx_errors; scalar_t__ tx_aborted_errors; scalar_t__ tx_carrier_errors; scalar_t__ tx_errors; } ;
struct TYPE_2__ {struct net_device_stats net_stats; } ;
struct usbdrv_private {TYPE_1__ drv_stats; } ;
struct net_device {struct usbdrv_private* ml_priv; } ;

/* Variables and functions */

struct net_device_stats * usbdrv_get_stats(struct net_device *dev)
{
    struct usbdrv_private *macp = dev->ml_priv;

    macp->drv_stats.net_stats.tx_errors =
        macp->drv_stats.net_stats.tx_carrier_errors +
        macp->drv_stats.net_stats.tx_aborted_errors;

    macp->drv_stats.net_stats.rx_errors =
        macp->drv_stats.net_stats.rx_crc_errors +
        macp->drv_stats.net_stats.rx_frame_errors +
        macp->drv_stats.net_stats.rx_length_errors;


    return &(macp->drv_stats.net_stats);
}