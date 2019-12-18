#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct nozomi {int last_ier; TYPE_2__* pdev; int /*<<< orphan*/  reg_fcr; int /*<<< orphan*/  reg_ier; TYPE_1__* port; } ;
typedef  enum port_type { ____Placeholder_port_type } port_type ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int toggle_ul; } ;

/* Variables and functions */
 int MDM_UL ; 
 int MDM_UL1 ; 
 int MDM_UL2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ send_data (int,struct nozomi*) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_data_ul(struct nozomi *dc, enum port_type port, u16 read_iir)
{
	u8 *toggle = &(dc->port[port].toggle_ul);

	if (*toggle == 0 && read_iir & MDM_UL1) {
		dc->last_ier &= ~MDM_UL;
		writew(dc->last_ier, dc->reg_ier);
		if (send_data(port, dc)) {
			writew(MDM_UL1, dc->reg_fcr);
			dc->last_ier = dc->last_ier | MDM_UL;
			writew(dc->last_ier, dc->reg_ier);
			*toggle = !*toggle;
		}

		if (read_iir & MDM_UL2) {
			dc->last_ier &= ~MDM_UL;
			writew(dc->last_ier, dc->reg_ier);
			if (send_data(port, dc)) {
				writew(MDM_UL2, dc->reg_fcr);
				dc->last_ier = dc->last_ier | MDM_UL;
				writew(dc->last_ier, dc->reg_ier);
				*toggle = !*toggle;
			}
		}

	} else if (*toggle == 1 && read_iir & MDM_UL2) {
		dc->last_ier &= ~MDM_UL;
		writew(dc->last_ier, dc->reg_ier);
		if (send_data(port, dc)) {
			writew(MDM_UL2, dc->reg_fcr);
			dc->last_ier = dc->last_ier | MDM_UL;
			writew(dc->last_ier, dc->reg_ier);
			*toggle = !*toggle;
		}

		if (read_iir & MDM_UL1) {
			dc->last_ier &= ~MDM_UL;
			writew(dc->last_ier, dc->reg_ier);
			if (send_data(port, dc)) {
				writew(MDM_UL1, dc->reg_fcr);
				dc->last_ier = dc->last_ier | MDM_UL;
				writew(dc->last_ier, dc->reg_ier);
				*toggle = !*toggle;
			}
		}
	} else {
		writew(read_iir & MDM_UL, dc->reg_fcr);
		dev_err(&dc->pdev->dev, "port out of sync!\n");
		return 0;
	}
	return 1;
}