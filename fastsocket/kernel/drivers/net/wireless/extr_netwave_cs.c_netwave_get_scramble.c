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
struct TYPE_2__ {int length; int /*<<< orphan*/  flags; } ;
union iwreq_data {TYPE_1__ encoding; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IW_ENCODE_ENABLED ; 
 int scramble_key ; 

__attribute__((used)) static int netwave_get_scramble(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu,
				char *key)
{
	key[1] = scramble_key & 0xff;
	key[0] = (scramble_key>>8) & 0xff;
	wrqu->encoding.flags = IW_ENCODE_ENABLED;
	wrqu->encoding.length = 2;
	return 0;
}