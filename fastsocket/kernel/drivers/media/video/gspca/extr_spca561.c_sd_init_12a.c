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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  init_161rev12A (struct gspca_dev*) ; 

__attribute__((used)) static int sd_init_12a(struct gspca_dev *gspca_dev)
{
	PDEBUG(D_STREAM, "Chip revision: 012a");
	init_161rev12A(gspca_dev);
	return 0;
}