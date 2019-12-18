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
struct TYPE_5__ {int /*<<< orphan*/  frmlen; int /*<<< orphan*/  data; int /*<<< orphan*/  rid; } ;
typedef  TYPE_1__ hfa384x_usb_rridresp_t ;
struct TYPE_6__ {int rid; int riddata_len; int /*<<< orphan*/  riddata; } ;
typedef  TYPE_2__ hfa384x_rridresult_t ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
usbctlx_get_rridresult(const hfa384x_usb_rridresp_t *rridresp,
		       hfa384x_rridresult_t *result)
{
	result->rid = le16_to_cpu(rridresp->rid);
	result->riddata = rridresp->data;
	result->riddata_len = ((le16_to_cpu(rridresp->frmlen) - 1) * 2);

}