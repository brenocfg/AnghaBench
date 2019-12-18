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
struct tape_device {TYPE_1__* cdev; } ;
struct TYPE_6__ {int emc; int* md; int smc; int /*<<< orphan*/  mdf; } ;
struct TYPE_5__ {TYPE_3__ f71; } ;
struct tape_3590_sense {TYPE_2__ fmt; } ;
struct irb {scalar_t__ ecw; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFSIZE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
tape_3590_print_dev_sim_msg_f2(struct tape_device *device, struct irb *irb)
{
	struct tape_3590_sense *sense;
	char *exception, *service;

	exception = kmalloc(BUFSIZE, GFP_ATOMIC);
	service = kmalloc(BUFSIZE, GFP_ATOMIC);

	if (!exception || !service)
		goto out_nomem;

	sense = (struct tape_3590_sense *) irb->ecw;
	/* Exception Message */
	switch (sense->fmt.f71.emc) {
	case 0x01:
		snprintf(exception, BUFSIZE, "Effect of failure is unknown");
		break;
	case 0x02:
		snprintf(exception, BUFSIZE, "DV Exception - no performance"
			" impact");
		break;
	case 0x03:
		snprintf(exception, BUFSIZE, "DV Exception on channel "
			"interface 0x%02x", sense->fmt.f71.md[0]);
		break;
	case 0x04:
		snprintf(exception, BUFSIZE, "DV Exception on loader 0x%02x",
			sense->fmt.f71.md[0]);
		break;
	case 0x05:
		snprintf(exception, BUFSIZE, "DV Exception on message display"
			" 0x%02x", sense->fmt.f71.md[0]);
		break;
	case 0x06:
		snprintf(exception, BUFSIZE, "DV Exception in tape path");
		break;
	case 0x07:
		snprintf(exception, BUFSIZE, "DV Exception in drive");
		break;
	default:
		snprintf(exception, BUFSIZE, "0x%02x",
			sense->fmt.f71.emc);
	}
	/* Service Message */
	switch (sense->fmt.f71.smc) {
	case 0x01:
		snprintf(service, BUFSIZE, "Repair impact is unknown");
		break;
	case 0x02:
		snprintf(service, BUFSIZE, "Repair will not impact device "
			"performance");
		break;
	case 0x03:
		if (sense->fmt.f71.mdf == 0)
			snprintf(service, BUFSIZE, "Repair will disable "
				"channel path 0x%x on DV",
				sense->fmt.f71.md[1]);
		else
			snprintf(service, BUFSIZE, "Repair will disable "
				"channel path (0x%x-0x%x) on DV",
				sense->fmt.f71.md[1], sense->fmt.f71.md[2]);
		break;
	case 0x04:
		if (sense->fmt.f71.mdf == 0)
			snprintf(service, BUFSIZE, "Repair will disable "
				"interface 0x%x on DV", sense->fmt.f71.md[1]);
		else
			snprintf(service, BUFSIZE, "Repair will disable "
				"interfaces (0x%x-0x%x) on DV",
				sense->fmt.f71.md[1], sense->fmt.f71.md[2]);
		break;
	case 0x05:
		if (sense->fmt.f71.mdf == 0)
			snprintf(service, BUFSIZE, "Repair will disable loader"
				" 0x%x on DV", sense->fmt.f71.md[1]);
		else
			snprintf(service, BUFSIZE, "Repair will disable loader"
				" (0x%x-0x%x) on DV",
				sense->fmt.f71.md[1], sense->fmt.f71.md[2]);
		break;
	case 0x07:
		snprintf(service, BUFSIZE, "Repair will disable access to DV");
		break;
	case 0x08:
		if (sense->fmt.f71.mdf == 0)
			snprintf(service, BUFSIZE, "Repair will disable "
				"message display 0x%x on DV",
				sense->fmt.f71.md[1]);
		else
			snprintf(service, BUFSIZE, "Repair will disable "
				"message displays (0x%x-0x%x) on DV",
				 sense->fmt.f71.md[1], sense->fmt.f71.md[2]);
		break;
	case 0x09:
		snprintf(service, BUFSIZE, "Clean DV");
		break;
	default:
		snprintf(service, BUFSIZE, "0x%02x",
			sense->fmt.f71.smc);
	}

	dev_warn (&device->cdev->dev, "Device subsystem information: exception"
		" %s, service %s\n", exception, service);
out_nomem:
	kfree(exception);
	kfree(service);
}