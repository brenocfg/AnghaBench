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
typedef  int /*<<< orphan*/  v4l2_std_id ;
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int V4L2_IN_ST_NO_SIGNAL ; 
 int /*<<< orphan*/  V4L2_STD_NTSC ; 
 int /*<<< orphan*/  V4L2_STD_PAL ; 
 int /*<<< orphan*/  V4L2_STD_SECAM ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int) ; 
 int vpx3220_fp_read (struct v4l2_subdev*,int) ; 

__attribute__((used)) static int vpx3220_status(struct v4l2_subdev *sd, u32 *pstatus, v4l2_std_id *pstd)
{
	int res = V4L2_IN_ST_NO_SIGNAL, status;
	v4l2_std_id std = 0;

	status = vpx3220_fp_read(sd, 0x0f3);

	v4l2_dbg(1, debug, sd, "status: 0x%04x\n", status);

	if (status < 0)
		return status;

	if ((status & 0x20) == 0) {
		res = 0;

		switch (status & 0x18) {
		case 0x00:
		case 0x10:
		case 0x14:
		case 0x18:
			std = V4L2_STD_PAL;
			break;

		case 0x08:
			std = V4L2_STD_SECAM;
			break;

		case 0x04:
		case 0x0c:
		case 0x1c:
			std = V4L2_STD_NTSC;
			break;
		}
	}
	if (pstd)
		*pstd = std;
	if (pstatus)
		*pstatus = status;
	return 0;
}