#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_15__ {int /*<<< orphan*/  SecureMode; } ;
struct TYPE_14__ {int Size; int* Buf; } ;
struct TYPE_13__ {TYPE_4__* Sock; } ;
typedef  TYPE_1__ RPC ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * BufToPack (TYPE_2__*) ; 
 int Endian32 (int) ; 
 int /*<<< orphan*/  Free (void*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 int MAX_PACK_SIZE ; 
 void* MallocEx (int,int) ; 
 TYPE_2__* NewBuf () ; 
 TYPE_2__* PackToBuf (int /*<<< orphan*/ *) ; 
 int RecvAll (TYPE_4__*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SeekBuf (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendAdd (TYPE_4__*,int*,int) ; 
 int SendNow (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_2__*,void*,int) ; 

PACK *RpcCallInternal(RPC *r, PACK *p)
{
	BUF *b;
	UINT size;
	PACK *ret;
	void *tmp;
	// Validate arguments
	if (r == NULL || p == NULL)
	{
		return NULL;
	}

	if (r->Sock == NULL)
	{
		return NULL;
	}

	b = PackToBuf(p);

	size = Endian32(b->Size);
	SendAdd(r->Sock, &size, sizeof(UINT));
	SendAdd(r->Sock, b->Buf, b->Size);
	FreeBuf(b);

	if (SendNow(r->Sock, r->Sock->SecureMode) == false)
	{
		return NULL;
	}

	if (RecvAll(r->Sock, &size, sizeof(UINT), r->Sock->SecureMode) == false)
	{
		return NULL;
	}

	size = Endian32(size);
	if (size > MAX_PACK_SIZE)
	{
		return NULL;
	}

	tmp = MallocEx(size, true);
	if (RecvAll(r->Sock, tmp, size, r->Sock->SecureMode) == false)
	{
		Free(tmp);
		return NULL;
	}

	b = NewBuf();
	WriteBuf(b, tmp, size);
	SeekBuf(b, 0, 0);
	Free(tmp);

	ret = BufToPack(b);
	if (ret == NULL)
	{
		FreeBuf(b);
		return NULL;
	}

	FreeBuf(b);

	return ret;
}