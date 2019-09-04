#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rand ;
typedef  int /*<<< orphan*/  hash ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int UINT ;
typedef  int UCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 int /*<<< orphan*/  GetCurrentMachineIpProcessHash (int*) ; 
 TYPE_1__* NewBuf () ; 
 int /*<<< orphan*/  Rand (int*,int) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha1 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemTime64 () ; 
 int /*<<< orphan*/  Tick64 () ; 
 int /*<<< orphan*/  TickHighres64 () ; 
 int /*<<< orphan*/  WriteBuf (TYPE_1__*,int*,int) ; 
 int /*<<< orphan*/  WriteBufInt64 (TYPE_1__*,int /*<<< orphan*/ ) ; 

void DCGenNewKey(UCHAR *key)
{
	BUF *b;
	UINT64 tick;
	UCHAR hash[SHA1_SIZE];
	UCHAR rand[SHA1_SIZE];
	UINT i;
	// Validate arguments
	if (key == NULL)
	{
		return;
	}

	b = NewBuf();

	Rand(rand, sizeof(rand));
	WriteBuf(b, rand, sizeof(rand));

	tick = TickHighres64();
	WriteBufInt64(b, tick);

	tick = Tick64();
	WriteBufInt64(b, tick);

	tick = SystemTime64();
	WriteBufInt64(b, tick);

	GetCurrentMachineIpProcessHash(hash);
	WriteBuf(b, hash, sizeof(hash));

	Sha1(key, b->Buf, b->Size);
	Rand(rand, sizeof(rand));

	for (i = 0;i < SHA1_SIZE;i++)
	{
		key[i] = key[i] ^ rand[i];
	}

	FreeBuf(b);
}