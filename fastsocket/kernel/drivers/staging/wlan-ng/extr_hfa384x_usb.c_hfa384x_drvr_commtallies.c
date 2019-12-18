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
typedef  int /*<<< orphan*/  hfa384x_t ;
struct TYPE_3__ {scalar_t__ parm2; scalar_t__ parm1; int /*<<< orphan*/  parm0; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_1__ hfa384x_metacmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  HFA384x_CMDCODE_INQ ; 
 int /*<<< orphan*/  HFA384x_IT_COMMTALLIES ; 
 int /*<<< orphan*/  hfa384x_docmd_async (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int hfa384x_drvr_commtallies(hfa384x_t *hw)
{
	hfa384x_metacmd_t cmd;

	cmd.cmd = HFA384x_CMDCODE_INQ;
	cmd.parm0 = HFA384x_IT_COMMTALLIES;
	cmd.parm1 = 0;
	cmd.parm2 = 0;

	hfa384x_docmd_async(hw, &cmd, NULL, NULL, NULL);

	return 0;
}