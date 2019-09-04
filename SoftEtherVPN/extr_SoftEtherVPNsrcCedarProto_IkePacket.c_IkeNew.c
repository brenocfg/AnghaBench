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
typedef  void* UINT64 ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_4__ {int FlagEncrypted; int FlagCommit; int FlagAuthOnly; int /*<<< orphan*/ * PayloadList; int /*<<< orphan*/  MessageId; int /*<<< orphan*/  ExchangeType; void* ResponderCookie; void* InitiatorCookie; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ IKE_PACKET ;

/* Variables and functions */
 TYPE_1__* ZeroMalloc (int) ; 

IKE_PACKET *IkeNew(UINT64 init_cookie, UINT64 resp_cookie, UCHAR exchange_type,
				   bool encrypted, bool commit, bool auth_only, UINT msg_id,
				   LIST *payload_list)
{
	IKE_PACKET *p = ZeroMalloc(sizeof(IKE_PACKET));

	p->InitiatorCookie = init_cookie;
	p->ResponderCookie = resp_cookie;
	p->ExchangeType = exchange_type;
	p->FlagEncrypted = encrypted;
	p->FlagCommit = commit;
	p->FlagAuthOnly = auth_only;
	p->MessageId = msg_id;
	p->PayloadList = payload_list;

	return p;
}