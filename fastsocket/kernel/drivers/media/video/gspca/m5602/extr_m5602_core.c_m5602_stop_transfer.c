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
struct sd {TYPE_1__* sensor; } ;
struct gspca_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* stop ) (struct sd*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct sd*) ; 

__attribute__((used)) static void m5602_stop_transfer(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	/* Run the sensor specific end transfer sequence */
	if (sd->sensor->stop)
		sd->sensor->stop(sd);
}