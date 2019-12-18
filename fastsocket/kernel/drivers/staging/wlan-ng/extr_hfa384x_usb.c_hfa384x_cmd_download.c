#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u16 ;
typedef  int /*<<< orphan*/  hfa384x_t ;
struct TYPE_3__ {int cmd; void* parm2; void* parm1; void* parm0; } ;
typedef  TYPE_1__ hfa384x_metacmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  HFA384x_CMDCODE_DOWNLD ; 
 int HFA384x_CMD_CMDCODE_SET (int /*<<< orphan*/ ) ; 
 int HFA384x_CMD_PROGMODE_SET (void*) ; 
 int hfa384x_docmd_wait (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pr_debug (char*,void*,void*,void*,void*) ; 

int hfa384x_cmd_download(hfa384x_t *hw, u16 mode, u16 lowaddr,
			 u16 highaddr, u16 codelen)
{
	int result = 0;
	hfa384x_metacmd_t cmd;

	pr_debug("mode=%d, lowaddr=0x%04x, highaddr=0x%04x, codelen=%d\n",
		 mode, lowaddr, highaddr, codelen);

	cmd.cmd = (HFA384x_CMD_CMDCODE_SET(HFA384x_CMDCODE_DOWNLD) |
		   HFA384x_CMD_PROGMODE_SET(mode));

	cmd.parm0 = lowaddr;
	cmd.parm1 = highaddr;
	cmd.parm2 = codelen;

	result = hfa384x_docmd_wait(hw, &cmd);

	return result;
}