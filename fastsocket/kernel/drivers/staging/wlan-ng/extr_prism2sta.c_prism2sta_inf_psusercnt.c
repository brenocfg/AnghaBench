#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ priv; } ;
typedef  TYPE_3__ wlandevice_t ;
struct TYPE_11__ {int /*<<< orphan*/  psusercount; } ;
typedef  TYPE_4__ hfa384x_t ;
struct TYPE_8__ {int /*<<< orphan*/  usercnt; } ;
struct TYPE_9__ {TYPE_1__ psusercnt; } ;
struct TYPE_12__ {TYPE_2__ info; } ;
typedef  TYPE_5__ hfa384x_InfFrame_t ;

/* Variables and functions */
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prism2sta_inf_psusercnt(wlandevice_t *wlandev,
				    hfa384x_InfFrame_t *inf)
{
	hfa384x_t *hw = (hfa384x_t *) wlandev->priv;

	hw->psusercount = le16_to_cpu(inf->info.psusercnt.usercnt);

	return;
}