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
typedef  int /*<<< orphan*/  u8 ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_r_1 (struct gspca_dev*,int) ; 

__attribute__((used)) static void spca504_read_info(struct gspca_dev *gspca_dev)
{
	int i;
	u8 info[6];

	for (i = 0; i < 6; i++)
		info[i] = reg_r_1(gspca_dev, i);
	PDEBUG(D_STREAM,
		"Read info: %d %d %d %d %d %d."
		" Should be 1,0,2,2,0,0",
		info[0], info[1], info[2],
		info[3], info[4], info[5]);
}