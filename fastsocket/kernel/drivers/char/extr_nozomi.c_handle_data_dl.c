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
struct nozomi {TYPE_1__* pdev; int /*<<< orphan*/  reg_fcr; } ;
typedef  enum port_type { ____Placeholder_port_type } port_type ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ receive_data (int,struct nozomi*) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_data_dl(struct nozomi *dc, enum port_type port, u8 *toggle,
			u16 read_iir, u16 mask1, u16 mask2)
{
	if (*toggle == 0 && read_iir & mask1) {
		if (receive_data(port, dc)) {
			writew(mask1, dc->reg_fcr);
			*toggle = !(*toggle);
		}

		if (read_iir & mask2) {
			if (receive_data(port, dc)) {
				writew(mask2, dc->reg_fcr);
				*toggle = !(*toggle);
			}
		}
	} else if (*toggle == 1 && read_iir & mask2) {
		if (receive_data(port, dc)) {
			writew(mask2, dc->reg_fcr);
			*toggle = !(*toggle);
		}

		if (read_iir & mask1) {
			if (receive_data(port, dc)) {
				writew(mask1, dc->reg_fcr);
				*toggle = !(*toggle);
			}
		}
	} else {
		dev_err(&dc->pdev->dev, "port out of sync!, toggle:%d\n",
			*toggle);
		return 0;
	}
	return 1;
}