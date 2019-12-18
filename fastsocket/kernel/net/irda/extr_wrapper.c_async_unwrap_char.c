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
struct net_device_stats {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  iobuff_t ;
typedef  int __u8 ;

/* Variables and functions */
#define  BOF 130 
#define  CE 129 
#define  EOF 128 
 int /*<<< orphan*/  async_unwrap_bof (struct net_device*,struct net_device_stats*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  async_unwrap_ce (struct net_device*,struct net_device_stats*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  async_unwrap_eof (struct net_device*,struct net_device_stats*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  async_unwrap_other (struct net_device*,struct net_device_stats*,int /*<<< orphan*/ *,int) ; 

void async_unwrap_char(struct net_device *dev,
		       struct net_device_stats *stats,
		       iobuff_t *rx_buff, __u8 byte)
{
	switch(byte) {
	case CE:
		async_unwrap_ce(dev, stats, rx_buff, byte);
		break;
	case BOF:
		async_unwrap_bof(dev, stats, rx_buff, byte);
		break;
	case EOF:
		async_unwrap_eof(dev, stats, rx_buff, byte);
		break;
	default:
		async_unwrap_other(dev, stats, rx_buff, byte);
		break;
	}
}