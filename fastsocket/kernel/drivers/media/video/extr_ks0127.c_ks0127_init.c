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
struct v4l2_subdev {int dummy; } ;
struct ks0127 {int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  KS_CMDE ; 
 int /*<<< orphan*/  KS_STAT ; 
 int /*<<< orphan*/  V4L2_IDENT_KS0122S ; 
 int /*<<< orphan*/  V4L2_IDENT_KS0127 ; 
 int /*<<< orphan*/  V4L2_IDENT_KS0127B ; 
 int /*<<< orphan*/  debug ; 
 int ks0127_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks0127_write (struct v4l2_subdev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/ * reg_defaults ; 
 struct ks0127* to_ks0127 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*) ; 

__attribute__((used)) static void ks0127_init(struct v4l2_subdev *sd)
{
	struct ks0127 *ks = to_ks0127(sd);
	u8 *table = reg_defaults;
	int i;

	ks->ident = V4L2_IDENT_KS0127;

	v4l2_dbg(1, debug, sd, "reset\n");
	msleep(1);

	/* initialize all registers to known values */
	/* (except STAT, 0x21, 0x22, TEST and 0x38,0x39) */

	for (i = 1; i < 33; i++)
		ks0127_write(sd, i, table[i]);

	for (i = 35; i < 40; i++)
		ks0127_write(sd, i, table[i]);

	for (i = 41; i < 56; i++)
		ks0127_write(sd, i, table[i]);

	for (i = 58; i < 64; i++)
		ks0127_write(sd, i, table[i]);


	if ((ks0127_read(sd, KS_STAT) & 0x80) == 0) {
		ks->ident = V4L2_IDENT_KS0122S;
		v4l2_dbg(1, debug, sd, "ks0122s found\n");
		return;
	}

	switch (ks0127_read(sd, KS_CMDE) & 0x0f) {
	case 0:
		v4l2_dbg(1, debug, sd, "ks0127 found\n");
		break;

	case 9:
		ks->ident = V4L2_IDENT_KS0127B;
		v4l2_dbg(1, debug, sd, "ks0127B Revision A found\n");
		break;

	default:
		v4l2_dbg(1, debug, sd, "unknown revision\n");
		break;
	}
}