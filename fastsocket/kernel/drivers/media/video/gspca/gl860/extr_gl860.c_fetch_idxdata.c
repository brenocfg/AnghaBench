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
struct idxdata {int /*<<< orphan*/  idx; int /*<<< orphan*/  data; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctrl_out (struct gspca_dev*,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

void fetch_idxdata(struct gspca_dev *gspca_dev, struct idxdata *tbl, int len)
{
	int n;

	for (n = 0; n < len; n++) {
		if (memcmp(tbl[n].data, "\xff\xff\xff", 3) != 0)
			ctrl_out(gspca_dev, 0x40, 3, 0x7a00, tbl[n].idx,
					3, tbl[n].data);
		else
			msleep(tbl[n].idx);
	}
}