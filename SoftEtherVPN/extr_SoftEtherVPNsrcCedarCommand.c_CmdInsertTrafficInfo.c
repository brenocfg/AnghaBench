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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  vv ;
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_6__ {int /*<<< orphan*/  BroadcastBytes; int /*<<< orphan*/  BroadcastCount; int /*<<< orphan*/  UnicastBytes; int /*<<< orphan*/  UnicastCount; } ;
struct TYPE_5__ {int /*<<< orphan*/  BroadcastBytes; int /*<<< orphan*/  BroadcastCount; int /*<<< orphan*/  UnicastBytes; int /*<<< orphan*/  UnicastCount; } ;
struct TYPE_7__ {TYPE_2__ Recv; TYPE_1__ Send; } ;
typedef  TYPE_3__ TRAFFIC ;
typedef  int /*<<< orphan*/  CT ;

/* Variables and functions */
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  ToStr3 (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _UU (char*) ; 

void CmdInsertTrafficInfo(CT *ct, TRAFFIC *t)
{
	wchar_t tmp[MAX_SIZE];
	char vv[128];
	// Validate arguments
	if (ct == NULL || t == NULL)
	{
		return;
	}

	// Transmission information
	ToStr3(vv, sizeof(vv), t->Send.UnicastCount);
	UniFormat(tmp, sizeof(tmp), _UU("SM_ST_NUM_PACKET_STR"), vv);
	CtInsert(ct, _UU("SM_ST_SEND_UCAST_NUM"), tmp);

	ToStr3(vv, sizeof(vv), t->Send.UnicastBytes);
	UniFormat(tmp, sizeof(tmp), _UU("SM_ST_SIZE_BYTE_STR"), vv);
	CtInsert(ct, _UU("SM_ST_SEND_UCAST_SIZE"), tmp);

	ToStr3(vv, sizeof(vv), t->Send.BroadcastCount);
	UniFormat(tmp, sizeof(tmp), _UU("SM_ST_NUM_PACKET_STR"), vv);
	CtInsert(ct, _UU("SM_ST_SEND_BCAST_NUM"), tmp);

	ToStr3(vv, sizeof(vv), t->Send.BroadcastBytes);
	UniFormat(tmp, sizeof(tmp), _UU("SM_ST_SIZE_BYTE_STR"), vv);
	CtInsert(ct, _UU("SM_ST_SEND_BCAST_SIZE"), tmp);

	// Reception information
	ToStr3(vv, sizeof(vv), t->Recv.UnicastCount);
	UniFormat(tmp, sizeof(tmp), _UU("SM_ST_NUM_PACKET_STR"), vv);
	CtInsert(ct, _UU("SM_ST_RECV_UCAST_NUM"), tmp);

	ToStr3(vv, sizeof(vv), t->Recv.UnicastBytes);
	UniFormat(tmp, sizeof(tmp), _UU("SM_ST_SIZE_BYTE_STR"), vv);
	CtInsert(ct, _UU("SM_ST_RECV_UCAST_SIZE"), tmp);

	ToStr3(vv, sizeof(vv), t->Recv.BroadcastCount);
	UniFormat(tmp, sizeof(tmp), _UU("SM_ST_NUM_PACKET_STR"), vv);
	CtInsert(ct, _UU("SM_ST_RECV_BCAST_NUM"), tmp);

	ToStr3(vv, sizeof(vv), t->Recv.BroadcastBytes);
	UniFormat(tmp, sizeof(tmp), _UU("SM_ST_SIZE_BYTE_STR"), vv);
	CtInsert(ct, _UU("SM_ST_RECV_BCAST_SIZE"), tmp);
}