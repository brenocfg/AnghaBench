#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ctrl_cnt; size_t ctrl_in_idx; TYPE_2__* ctrl_buff; } ;
typedef  TYPE_1__ hfcusb_data ;
struct TYPE_6__ {int action; void* reg_val; void* hfc_reg; } ;
typedef  TYPE_2__ ctrl_buft ;
typedef  void* __u8 ;

/* Variables and functions */
 int HFC_CTRL_BUFSIZE ; 
 int /*<<< orphan*/  ctrl_start_transfer (TYPE_1__*) ; 

__attribute__((used)) static int
queue_control_request(hfcusb_data * hfc, __u8 reg, __u8 val, int action)
{
	ctrl_buft *buf;

	if (hfc->ctrl_cnt >= HFC_CTRL_BUFSIZE)
		return (1);	/* no space left */
	buf = &hfc->ctrl_buff[hfc->ctrl_in_idx];	/* pointer to new index */
	buf->hfc_reg = reg;
	buf->reg_val = val;
	buf->action = action;
	if (++hfc->ctrl_in_idx >= HFC_CTRL_BUFSIZE)
		hfc->ctrl_in_idx = 0;	/* pointer wrap */
	if (++hfc->ctrl_cnt == 1)
		ctrl_start_transfer(hfc);
	return (0);
}