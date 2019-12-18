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
struct net_device {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
struct chbk {TYPE_1__* cdev; struct net_device* ndev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAW_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static void
ccw_check_unit_check(struct chbk * p_ch, unsigned char sense )
{
	struct net_device *ndev = p_ch->ndev;
	struct device *dev = &p_ch->cdev->dev;

	CLAW_DBF_TEXT(4, trace, "unitchek");
	dev_warn(dev, "The communication peer of %s disconnected\n",
		ndev->name);

	if (sense & 0x40) {
		if (sense & 0x01) {
			dev_warn(dev, "The remote channel adapter for"
				" %s has been reset\n",
				ndev->name);
		}
	} else if (sense & 0x20) {
		if (sense & 0x04) {
			dev_warn(dev, "A data streaming timeout occurred"
				" for %s\n",
				ndev->name);
		} else if (sense & 0x10) {
			dev_warn(dev, "The remote channel adapter for %s"
				" is faulty\n",
				ndev->name);
		} else {
			dev_warn(dev, "A data transfer parity error occurred"
				" for %s\n",
				ndev->name);
		}
	} else if (sense & 0x10) {
		dev_warn(dev, "A read data parity error occurred"
			" for %s\n",
			ndev->name);
	}

}