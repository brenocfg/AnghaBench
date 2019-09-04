#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int UCHAR ;
struct TYPE_24__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_23__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_20__ {int /*<<< orphan*/  CryptoKeySize; int /*<<< orphan*/  Crypto; int /*<<< orphan*/ * Hash; } ;
struct TYPE_22__ {TYPE_1__ TransformSetting; int /*<<< orphan*/  HashSize; int /*<<< orphan*/  SKEYID_e; int /*<<< orphan*/ * CryptoKey; int /*<<< orphan*/  SKEYID; int /*<<< orphan*/  ResponderCookie; int /*<<< orphan*/  InitiatorCookie; TYPE_7__* DhSharedKey; int /*<<< orphan*/  SKEYID_a; int /*<<< orphan*/  SKEYID_d; TYPE_7__* InitiatorRand; TYPE_7__* ResponderRand; int /*<<< orphan*/  Secret; } ;
struct TYPE_21__ {char* Secret; } ;
typedef  TYPE_2__ IKE_SERVER ;
typedef  TYPE_3__ IKE_SA ;
typedef  int /*<<< orphan*/  IKE_HASH ;
typedef  TYPE_4__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  BinToStrEx (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* CloneBuf (TYPE_7__*) ; 
 int /*<<< orphan*/  Debug (char*,char*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_4__*) ; 
 int /*<<< orphan*/  IkeFreeKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IkeHMac (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IkeHMacBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/ * IkeNewCryptoKeyFromK (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* IkeStrToPassword (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 TYPE_4__* MemToBuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SeekBufToEnd (TYPE_4__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_4__*,int*,int) ; 
 int /*<<< orphan*/  WriteBufBuf (TYPE_4__*,TYPE_7__*) ; 
 int /*<<< orphan*/  WriteBufInt64 (TYPE_4__*,int /*<<< orphan*/ ) ; 

void IkeCalcSaKeySet(IKE_SERVER *ike, IKE_SA *sa, char *secret)
{
	BUF *secret_buf;
	BUF *rand_buf;
	BUF *d_buf, *a_buf, *e_buf;
	UCHAR u;
	IKE_HASH *h;
	char tmp[MAX_SIZE];
	// Validate arguments
	if (ike == NULL || sa == NULL)
	{
		return;
	}

	h = sa->TransformSetting.Hash;

	// Calculation of SKEYID
	StrCpy(sa->Secret, sizeof(sa->Secret), secret == NULL ? ike->Secret : secret);
	secret_buf = IkeStrToPassword(sa->Secret);
	rand_buf = CloneBuf(sa->ResponderRand);
	SeekBufToEnd(rand_buf);
	BinToStrEx(tmp, sizeof(tmp), rand_buf->Buf, rand_buf->Size);
	Debug("ResponderRand: %s\n", tmp);
	BinToStrEx(tmp, sizeof(tmp), sa->InitiatorRand->Buf, sa->InitiatorRand->Size);
	Debug("InitiatorRand: %s\n", tmp);

	WriteBufBuf(rand_buf, sa->InitiatorRand);

	IkeHMacBuf(h, sa->SKEYID, secret_buf, rand_buf);

	BinToStrEx(tmp, sizeof(tmp), sa->SKEYID, sa->HashSize);
	Debug("SKEYID: %s\n", tmp);

	// SKEYID_d
	d_buf = CloneBuf(sa->DhSharedKey);
	SeekBufToEnd(d_buf);
	WriteBufInt64(d_buf, sa->InitiatorCookie);
	WriteBufInt64(d_buf, sa->ResponderCookie);
	u = 0;
	WriteBuf(d_buf, &u, 1);
	IkeHMac(h, sa->SKEYID_d, sa->SKEYID, sa->HashSize, d_buf->Buf, d_buf->Size);

	BinToStrEx(tmp, sizeof(tmp), sa->SKEYID_d, sa->HashSize);
	Debug("SKEYID_d: %s\n", tmp);

	// SKEYID_a
	a_buf = MemToBuf(sa->SKEYID_d, sa->HashSize);
	SeekBufToEnd(a_buf);
	WriteBufBuf(a_buf, sa->DhSharedKey);
	WriteBufInt64(a_buf, sa->InitiatorCookie);
	WriteBufInt64(a_buf, sa->ResponderCookie);
	u = 1;
	WriteBuf(a_buf, &u, 1);
	IkeHMac(h, sa->SKEYID_a, sa->SKEYID, sa->HashSize, a_buf->Buf, a_buf->Size);

	BinToStrEx(tmp, sizeof(tmp), sa->SKEYID_a, sa->HashSize);
	Debug("SKEYID_a: %s\n", tmp);

	// SKEYID_e
	e_buf = MemToBuf(sa->SKEYID_a, sa->HashSize);
	SeekBufToEnd(e_buf);
	WriteBufBuf(e_buf, sa->DhSharedKey);
	WriteBufInt64(e_buf, sa->InitiatorCookie);
	WriteBufInt64(e_buf, sa->ResponderCookie);
	u = 2;
	WriteBuf(e_buf, &u, 1);
	IkeHMac(h, sa->SKEYID_e, sa->SKEYID, sa->HashSize, e_buf->Buf, e_buf->Size);

	BinToStrEx(tmp, sizeof(tmp), sa->SKEYID_e, sa->HashSize);
	Debug("SKEYID_e: %s\n", tmp);

	if (sa->CryptoKey != NULL)
	{
		IkeFreeKey(sa->CryptoKey);
	}

	sa->CryptoKey = IkeNewCryptoKeyFromK(ike, sa->SKEYID_e, sa->HashSize, sa->TransformSetting.Hash,
		sa->TransformSetting.Crypto, sa->TransformSetting.CryptoKeySize);

	// Release the memory
	FreeBuf(secret_buf);
	FreeBuf(rand_buf);
	FreeBuf(d_buf);
	FreeBuf(a_buf);
	FreeBuf(e_buf);
}