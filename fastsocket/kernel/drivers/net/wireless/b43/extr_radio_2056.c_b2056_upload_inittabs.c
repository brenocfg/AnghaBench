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
struct TYPE_2__ {size_t rev; } ;
struct b43_wldev {TYPE_1__ phy; } ;
struct b2056_inittabs_pts {int /*<<< orphan*/  rx_length; int /*<<< orphan*/  rx; int /*<<< orphan*/  tx_length; int /*<<< orphan*/  tx; int /*<<< orphan*/  syn_length; int /*<<< orphan*/  syn; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct b2056_inittabs_pts*) ; 
 int /*<<< orphan*/  B2056_RX0 ; 
 int /*<<< orphan*/  B2056_RX1 ; 
 int /*<<< orphan*/  B2056_SYN ; 
 int /*<<< orphan*/  B2056_TX0 ; 
 int /*<<< orphan*/  B2056_TX1 ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 struct b2056_inittabs_pts* b2056_inittabs ; 
 int /*<<< orphan*/  b2056_upload_inittab (struct b43_wldev*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void b2056_upload_inittabs(struct b43_wldev *dev,
			   bool ghz5, bool ignore_uploadflag)
{
	const struct b2056_inittabs_pts *pts;

	if (dev->phy.rev >= ARRAY_SIZE(b2056_inittabs)) {
		B43_WARN_ON(1);
		return;
	}
	pts = &b2056_inittabs[dev->phy.rev];

	b2056_upload_inittab(dev, ghz5, ignore_uploadflag,
				B2056_SYN, pts->syn, pts->syn_length);
	b2056_upload_inittab(dev, ghz5, ignore_uploadflag,
				B2056_TX0, pts->tx, pts->tx_length);
	b2056_upload_inittab(dev, ghz5, ignore_uploadflag,
				B2056_TX1, pts->tx, pts->tx_length);
	b2056_upload_inittab(dev, ghz5, ignore_uploadflag,
				B2056_RX0, pts->rx, pts->rx_length);
	b2056_upload_inittab(dev, ghz5, ignore_uploadflag,
				B2056_RX1, pts->rx, pts->rx_length);
}