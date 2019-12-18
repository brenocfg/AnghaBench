#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_10__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_9__ {int /*<<< orphan*/  DummyMark; int /*<<< orphan*/  DummyDestIP; int /*<<< orphan*/  DummySrcIp; } ;
typedef  int /*<<< orphan*/  PRAND ;
typedef  TYPE_1__ IPTABLES_ENTRY ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 int /*<<< orphan*/  FreePRand (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GenerateDummyIp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GenerateDummyMark (int /*<<< orphan*/ *) ; 
 TYPE_2__* NewBuf () ; 
 int /*<<< orphan*/ * NewPRand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA1_SIZE ; 
 int /*<<< orphan*/  WriteBuf (TYPE_2__*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBufInt (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBufStr (TYPE_2__*,char*) ; 

void GenerateDummyIpAndMark(void *hash_seed, IPTABLES_ENTRY *e, UINT id)
{
	PRAND *p;
	BUF *b;
	if (hash_seed == NULL || e == NULL)
	{
		return;
	}

	b = NewBuf();
	WriteBufInt(b, id);
	WriteBuf(b, hash_seed, SHA1_SIZE);
	WriteBufStr(b, "20151002");

	p = NewPRand(b->Buf, b->Size);
	FreeBuf(b);

	GenerateDummyIp(p, &e->DummySrcIp);
	GenerateDummyIp(p, &e->DummyDestIP);
	e->DummyMark = GenerateDummyMark(p);

	FreePRand(p);
}