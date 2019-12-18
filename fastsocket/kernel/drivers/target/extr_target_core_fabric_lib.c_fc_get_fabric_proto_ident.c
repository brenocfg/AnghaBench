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
typedef  int u8 ;
struct se_portal_group {int dummy; } ;

/* Variables and functions */

u8 fc_get_fabric_proto_ident(struct se_portal_group *se_tpg)
{
	return 0x0;	/* 0 = fcp-2 per SPC4 section 7.5.1 */
}