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
struct tape_request {scalar_t__ op; } ;
struct tape_device {TYPE_1__* cdev; } ;
struct irb {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ TO_ASSIGN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int tape_34xx_erp_failed (struct tape_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tape_dump_sense_dbf (struct tape_device*,struct tape_request*,struct irb*) ; 

__attribute__((used)) static int
tape_34xx_erp_bug(struct tape_device *device, struct tape_request *request,
		  struct irb *irb, int no)
{
	if (request->op != TO_ASSIGN) {
		dev_err(&device->cdev->dev, "An unexpected condition %d "
			"occurred in tape error recovery\n", no);
		tape_dump_sense_dbf(device, request, irb);
	}
	return tape_34xx_erp_failed(request, -EIO);
}