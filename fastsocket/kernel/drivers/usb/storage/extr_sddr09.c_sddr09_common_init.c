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
struct us_data {int /*<<< orphan*/  extra_destructor; int /*<<< orphan*/  extra; TYPE_3__* pusb_dev; } ;
struct sddr09_card_info {int dummy; } ;
struct TYPE_6__ {TYPE_2__* actconfig; } ;
struct TYPE_4__ {int bConfigurationValue; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPIPE ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  US_DEBUGP (char*,...) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_init_ecc () ; 
 int /*<<< orphan*/  sddr09_card_info_destructor ; 
 int usb_reset_configuration (TYPE_3__*) ; 

__attribute__((used)) static int
sddr09_common_init(struct us_data *us) {
	int result;

	/* set the configuration -- STALL is an acceptable response here */
	if (us->pusb_dev->actconfig->desc.bConfigurationValue != 1) {
		US_DEBUGP("active config #%d != 1 ??\n", us->pusb_dev
				->actconfig->desc.bConfigurationValue);
		return -EINVAL;
	}

	result = usb_reset_configuration(us->pusb_dev);
	US_DEBUGP("Result of usb_reset_configuration is %d\n", result);
	if (result == -EPIPE) {
		US_DEBUGP("-- stall on control interface\n");
	} else if (result != 0) {
		/* it's not a stall, but another error -- time to bail */
		US_DEBUGP("-- Unknown error.  Rejecting device\n");
		return -EINVAL;
	}

	us->extra = kzalloc(sizeof(struct sddr09_card_info), GFP_NOIO);
	if (!us->extra)
		return -ENOMEM;
	us->extra_destructor = sddr09_card_info_destructor;

	nand_init_ecc();
	return 0;
}