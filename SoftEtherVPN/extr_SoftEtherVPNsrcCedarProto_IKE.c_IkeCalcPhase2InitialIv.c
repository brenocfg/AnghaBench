#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_12__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_10__ {TYPE_1__* Crypto; int /*<<< orphan*/  Hash; } ;
struct TYPE_11__ {int BlockSize; TYPE_2__ TransformSetting; int /*<<< orphan*/ * Iv; } ;
struct TYPE_9__ {int /*<<< orphan*/  BlockSize; } ;
typedef  TYPE_3__ IKE_SA ;
typedef  TYPE_4__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Endian32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_4__*) ; 
 int IKE_MAX_HASH_SIZE ; 
 int /*<<< orphan*/  IkeHash (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* NewBuf () ; 
 int /*<<< orphan*/  WriteBuf (TYPE_4__*,int /*<<< orphan*/ *,int) ; 

void IkeCalcPhase2InitialIv(void *iv, IKE_SA *sa, UINT message_id)
{
	BUF *b;
	UCHAR hash[IKE_MAX_HASH_SIZE];
	// Validate arguments
	if (iv == NULL || sa == NULL)
	{
		return;
	}

	message_id = Endian32(message_id);

	b = NewBuf();
	WriteBuf(b, sa->Iv, sa->BlockSize);
	WriteBuf(b, &message_id, sizeof(UINT));

	IkeHash(sa->TransformSetting.Hash, hash, b->Buf, b->Size);

	Copy(iv, hash, sa->TransformSetting.Crypto->BlockSize);

	FreeBuf(b);
}