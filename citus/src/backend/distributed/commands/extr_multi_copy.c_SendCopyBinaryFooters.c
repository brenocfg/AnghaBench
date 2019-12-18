#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_4__ {int /*<<< orphan*/  fe_msgbuf; } ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__* CopyOutState ;

/* Variables and functions */
 int /*<<< orphan*/  AppendCopyBinaryFooters (TYPE_1__*) ; 
 int /*<<< orphan*/  SendCopyDataToAll (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resetStringInfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
SendCopyBinaryFooters(CopyOutState copyOutState, int64 shardId, List *connectionList)
{
	resetStringInfo(copyOutState->fe_msgbuf);
	AppendCopyBinaryFooters(copyOutState);
	SendCopyDataToAll(copyOutState->fe_msgbuf, shardId, connectionList);
}