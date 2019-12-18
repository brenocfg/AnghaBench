#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hash ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_9__ {int Size; int /*<<< orphan*/ * Buf; } ;
struct TYPE_8__ {scalar_t__ Type; int /*<<< orphan*/  SecureMode; } ;
typedef  TYPE_1__ SOCK ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Endian32 (int) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 TYPE_2__* PackToBuf (int /*<<< orphan*/ *) ; 
 int SHA1_SIZE ; 
 scalar_t__ SOCK_TCP ; 
 int /*<<< orphan*/  SendAdd (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int SendNow (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sha1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

bool SendPackWithHash(SOCK *s, PACK *p)
{
	BUF *b;
	UINT sz;
	UCHAR hash[SHA1_SIZE];
	// Validate arguments
	if (s == NULL || p == NULL || s->Type != SOCK_TCP)
	{
		return false;
	}

	b = PackToBuf(p);
	sz = Endian32(b->Size);

	SendAdd(s, &sz, sizeof(UINT));
	SendAdd(s, b->Buf, b->Size);
	Sha1(hash, b->Buf, b->Size);
	SendAdd(s, hash, sizeof(hash));

	FreeBuf(b);

	return SendNow(s, s->SecureMode);
}