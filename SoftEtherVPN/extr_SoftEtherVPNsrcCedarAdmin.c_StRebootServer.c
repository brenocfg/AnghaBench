#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_11__ {TYPE_2__* Server; } ;
struct TYPE_10__ {int /*<<< orphan*/  IntValue; } ;
struct TYPE_9__ {TYPE_1__* Cedar; } ;
struct TYPE_8__ {int /*<<< orphan*/  Bridge; } ;
typedef  TYPE_3__ RPC_TEST ;
typedef  TYPE_4__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_4__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  SERVER_ADMIN_ONLY ; 
 int /*<<< orphan*/  SiRebootServerEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

UINT StRebootServer(ADMIN *a, RPC_TEST *t)
{
	SERVER_ADMIN_ONLY;

	ALog(a, NULL, "LA_REBOOT_SERVER");

	SiRebootServerEx(a->Server->Cedar->Bridge, t->IntValue);

	return ERR_NO_ERROR;
}