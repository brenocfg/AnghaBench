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
typedef  int u8 ;
typedef  int u16 ;
struct cam_data {int /*<<< orphan*/  lowlevel_data; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* transferCmd ) (int /*<<< orphan*/ ,int*,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int) ; 
 int stub1 (int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static int do_command_extended(struct cam_data *cam, u16 command,
			       u8 a, u8 b, u8 c, u8 d,
			       u8 e, u8 f, u8 g, u8 h,
			       u8 i, u8 j, u8 k, u8 l)
{
	int retval;
	u8 cmd[8], data[8];

	cmd[0] = command>>8;
	cmd[1] = command&0xff;
	cmd[2] = a;
	cmd[3] = b;
	cmd[4] = c;
	cmd[5] = d;
	cmd[6] = 8;
	cmd[7] = 0;
	data[0] = e;
	data[1] = f;
	data[2] = g;
	data[3] = h;
	data[4] = i;
	data[5] = j;
	data[6] = k;
	data[7] = l;

	retval = cam->ops->transferCmd(cam->lowlevel_data, cmd, data);
	if (retval)
		DBG("%x - failed\n", command);

	return retval;
}