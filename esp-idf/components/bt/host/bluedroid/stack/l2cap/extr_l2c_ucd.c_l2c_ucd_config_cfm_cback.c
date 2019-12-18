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
typedef  int /*<<< orphan*/  tL2CAP_CFG_INFO ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */

__attribute__((used)) static void l2c_ucd_config_cfm_cback (UINT16 cid, tL2CAP_CFG_INFO *p_cfg)
{
    /* do nothing */
}