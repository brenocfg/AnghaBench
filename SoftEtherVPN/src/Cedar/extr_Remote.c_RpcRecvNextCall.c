#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_17__ {int Size; int* Buf; } ;
struct TYPE_16__ {TYPE_1__* Sock; } ;
struct TYPE_15__ {int /*<<< orphan*/  SecureMode; } ;
typedef  TYPE_1__ SOCK ;
typedef  TYPE_2__ RPC ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_3__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * BufToPack (TYPE_3__*) ; 
 int /*<<< orphan*/ * CallRpcDispatcher (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_NOT_SUPPORTED ; 
 int Endian32 (int) ; 
 int /*<<< orphan*/  Free (void*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_3__*) ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int MAX_PACK_SIZE ; 
 void* MallocEx (int,int) ; 
 TYPE_3__* NewBuf () ; 
 int /*<<< orphan*/ * PackError (int /*<<< orphan*/ ) ; 
 TYPE_3__* PackToBuf (int /*<<< orphan*/ *) ; 
 int RecvAll (TYPE_1__*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SeekBuf (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendAdd (TYPE_1__*,int*,int) ; 
 int SendNow (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_3__*,void*,int) ; 

bool RpcRecvNextCall(RPC *r)
{
	UINT size;
	void *tmp;
	SOCK *s;
	BUF *b;
	PACK *p;
	PACK *ret;
	// Validate arguments
	if (r == NULL)
	{
		return false;
	}

	s = r->Sock;

	if (RecvAll(s, &size, sizeof(UINT), s->SecureMode) == false)
	{
		return false;
	}

	size = Endian32(size);

	if (size > MAX_PACK_SIZE)
	{
		return false;
	}

	tmp = MallocEx(size, true);

	if (RecvAll(s, tmp, size, s->SecureMode) == false)
	{
		Free(tmp);
		return false;
	}

	b = NewBuf();
	WriteBuf(b, tmp, size);
	SeekBuf(b, 0, 0);
	Free(tmp);

	p = BufToPack(b);
	FreeBuf(b);

	if (p == NULL)
	{
		return false;
	}

	ret = CallRpcDispatcher(r, p);
	FreePack(p);

	if (ret == NULL)
	{
		ret = PackError(ERR_NOT_SUPPORTED);
	}

	b = PackToBuf(ret);
	FreePack(ret);

	size = Endian32(b->Size);
	SendAdd(s, &size, sizeof(UINT));
	SendAdd(s, b->Buf, b->Size);

	if (SendNow(s, s->SecureMode) == false)
	{
		FreeBuf(b);
		return false;
	}

	FreeBuf(b);

	return true;
}