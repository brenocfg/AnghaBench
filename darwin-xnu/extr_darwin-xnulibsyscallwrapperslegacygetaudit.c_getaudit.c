#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  machine; int /*<<< orphan*/  port; } ;
struct auditinfo {int /*<<< orphan*/  ai_asid; TYPE_1__ ai_termid; int /*<<< orphan*/  ai_mask; int /*<<< orphan*/  ai_auid; } ;
struct TYPE_6__ {int /*<<< orphan*/ * at_addr; int /*<<< orphan*/  at_port; } ;
struct TYPE_7__ {int /*<<< orphan*/  ai_asid; TYPE_2__ ai_termid; int /*<<< orphan*/  ai_mask; int /*<<< orphan*/  ai_auid; } ;
typedef  TYPE_3__ auditinfo_addr_t ;
typedef  int /*<<< orphan*/  aia ;

/* Variables and functions */
 int getaudit_addr (TYPE_3__*,int) ; 

int
getaudit(struct auditinfo *ainfo)
{
	int err;
	auditinfo_addr_t aia;

	if ((err = getaudit_addr(&aia, sizeof(aia))) != 0)
		return (err);

	ainfo->ai_auid = aia.ai_auid;
	ainfo->ai_mask = aia.ai_mask;
	ainfo->ai_termid.port = aia.ai_termid.at_port;
	ainfo->ai_termid.machine = aia.ai_termid.at_addr[0];
	ainfo->ai_asid = aia.ai_asid;

	return (0);
}