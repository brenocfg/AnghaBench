#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_9__ {int /*<<< orphan*/  HashedPassword; } ;
struct TYPE_8__ {TYPE_5__* Server; } ;
struct TYPE_7__ {int /*<<< orphan*/  HashedPassword; int /*<<< orphan*/  PlainTextPassword; } ;
typedef  TYPE_1__ RPC_SET_PASSWORD ;
typedef  TYPE_2__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_2__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  HashAdminPassword (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_5__*) ; 
 scalar_t__ IsZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SERVER_ADMIN_ONLY ; 
 int /*<<< orphan*/  SHA1_SIZE ; 

UINT StSetServerPassword(ADMIN *a, RPC_SET_PASSWORD *t)
{
	SERVER_ADMIN_ONLY;

	if (IsZero(t->HashedPassword, sizeof(t->HashedPassword)))
	{
		// For JSON-RPC
		HashAdminPassword(t->HashedPassword, t->PlainTextPassword);
	}

	Copy(a->Server->HashedPassword, t->HashedPassword, SHA1_SIZE);

	ALog(a, NULL, "LA_SET_SERVER_PASSWORD");

	IncrementServerConfigRevision(a->Server);

	return ERR_NO_ERROR;
}