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
struct urb {scalar_t__ context; } ;
struct gspca_dev {int /*<<< orphan*/  streaming; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_PACK ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fill_frame (struct gspca_dev*,struct urb*) ; 

__attribute__((used)) static void isoc_irq(struct urb *urb)
{
	struct gspca_dev *gspca_dev = (struct gspca_dev *) urb->context;

	PDEBUG(D_PACK, "isoc irq");
	if (!gspca_dev->streaming)
		return;
	fill_frame(gspca_dev, urb);
}