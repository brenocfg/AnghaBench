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
struct ampdu_info {TYPE_1__* wlc; } ;
struct TYPE_2__ {int /*<<< orphan*/  pri_scb; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_c_scb_ampdu_update_config (struct ampdu_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void brcms_c_scb_ampdu_update_config_all(struct ampdu_info *ampdu)
{
	brcms_c_scb_ampdu_update_config(ampdu, &ampdu->wlc->pri_scb);
}