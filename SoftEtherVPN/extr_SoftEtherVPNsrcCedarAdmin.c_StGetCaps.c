#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  Server; } ;
typedef  int /*<<< orphan*/  CAPSLIST ;
typedef  TYPE_1__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeRpcCapsList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetServerCapsMain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

UINT StGetCaps(ADMIN *a, CAPSLIST *t)
{
	FreeRpcCapsList(t);
	Zero(t, sizeof(CAPSLIST));

	GetServerCapsMain(a->Server, t);

	return ERR_NO_ERROR;
}