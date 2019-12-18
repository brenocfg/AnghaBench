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
struct TYPE_3__ {int /*<<< orphan*/ * Buffer; int /*<<< orphan*/  Offset; int /*<<< orphan*/  ServerName; int /*<<< orphan*/  FilePath; } ;
typedef  TYPE_1__ RPC_READ_LOG_FILE ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddBuf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcReadLogFile(PACK *p, RPC_READ_LOG_FILE *t)
{
	// Validate arguments
	if (p == NULL || t == NULL)
	{
		return;
	}

	PackAddStr(p, "FilePath", t->FilePath);
	PackAddStr(p, "ServerName", t->ServerName);
	PackAddInt(p, "Offset", t->Offset);

	if (t->Buffer != NULL)
	{
		PackAddBuf(p, "Buffer", t->Buffer);
	}
}