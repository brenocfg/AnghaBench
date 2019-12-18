#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; int /*<<< orphan*/  length; } ;
union iwreq_data {TYPE_3__ essid; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
struct TYPE_5__ {TYPE_1__ el; int /*<<< orphan*/  essid; } ;
struct wl3501_card {int /*<<< orphan*/  lock; TYPE_2__ essid; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wl3501_card* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int wl3501_get_essid(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *wrqu, char *extra)
{
	struct wl3501_card *this = netdev_priv(dev);
	unsigned long flags;

	spin_lock_irqsave(&this->lock, flags);
	wrqu->essid.flags  = 1;
	wrqu->essid.length = this->essid.el.len;
	memcpy(extra, this->essid.essid, this->essid.el.len);
	spin_unlock_irqrestore(&this->lock, flags);
	return 0;
}