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
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_out (struct gspca_dev*,int,int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dat_common00 ; 
 int /*<<< orphan*/ * dat_common01 ; 
 int /*<<< orphan*/ * dat_common02 ; 
 int /*<<< orphan*/ * dat_common03 ; 
 int /*<<< orphan*/ * dat_common04 ; 
 int /*<<< orphan*/ * dat_common05 ; 
 int /*<<< orphan*/ * dat_common06 ; 
 int /*<<< orphan*/ * dat_common07 ; 
 int /*<<< orphan*/ * dat_common08 ; 
 int /*<<< orphan*/ * dat_common09 ; 
 int /*<<< orphan*/ * dat_common10 ; 
 int /*<<< orphan*/ * dat_common11 ; 
 int /*<<< orphan*/  fetch_validx (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keep_on_fetching_validx (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tbl_common ; 

__attribute__((used)) static void common(struct gspca_dev *gspca_dev)
{
	s32 n; /* reserved for FETCH functions */

	ctrl_out(gspca_dev, 0x40, 3, 0x0000, 0x0200, 22, dat_common00);
	ctrl_out(gspca_dev, 0x40, 1, 0x0041, 0x0000, 0, NULL);
	ctrl_out(gspca_dev, 0x40, 3, 0xba00, 0x0200, 32, dat_common01);
	n = fetch_validx(gspca_dev, tbl_common, ARRAY_SIZE(tbl_common));
	ctrl_out(gspca_dev, 0x40, 3, 0xba00, 0x0200, 48, dat_common02);
	ctrl_out(gspca_dev, 0x40, 3, 0xba00, 0x0200, 48, dat_common03);
	ctrl_out(gspca_dev, 0x40, 3, 0xba00, 0x0200, 16, dat_common04);
	ctrl_out(gspca_dev, 0x40, 3, 0xba00, 0x0200, 48, dat_common05);
	ctrl_out(gspca_dev, 0x40, 3, 0xba00, 0x0200, 44, dat_common06);
	keep_on_fetching_validx(gspca_dev, tbl_common,
					ARRAY_SIZE(tbl_common), n);
	ctrl_out(gspca_dev, 0x40, 3, 0xba00, 0x0200, 52, dat_common07);
	ctrl_out(gspca_dev, 0x40, 3, 0xba00, 0x0200, 48, dat_common08);
	ctrl_out(gspca_dev, 0x40, 3, 0xba00, 0x0200, 48, dat_common09);
	ctrl_out(gspca_dev, 0x40, 3, 0xba00, 0x0200, 56, dat_common10);
	keep_on_fetching_validx(gspca_dev, tbl_common,
					ARRAY_SIZE(tbl_common), n);
	ctrl_out(gspca_dev, 0x40, 3, 0xba00, 0x0200, 40, dat_common11);
	keep_on_fetching_validx(gspca_dev, tbl_common,
					ARRAY_SIZE(tbl_common), n);
}