#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sign ;
typedef  int /*<<< orphan*/  hash ;
typedef  int /*<<< orphan*/  X ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_10__ {int Size; int /*<<< orphan*/ * Buf; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  K ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 TYPE_1__* NewBuf () ; 
 TYPE_1__* PackToBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RsaSign (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  SeekBuf (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sha1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WpcAddDataEntryBin (TYPE_1__*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* XToBuf (int /*<<< orphan*/ *,int) ; 

BUF *WpcGeneratePacket(PACK *pack, X *cert, K *key)
{
	UCHAR hash[SHA1_SIZE];
	BUF *pack_data;
	BUF *cert_data = NULL;
	BUF *sign_data = NULL;
	BUF *b;
	// Validate arguments
	if (pack == NULL)
	{
		return NULL;
	}

	pack_data = PackToBuf(pack);
	Sha1(hash, pack_data->Buf, pack_data->Size);

	if (cert != NULL && key != NULL)
	{
		UCHAR sign[128];
		cert_data = XToBuf(cert, false);

		RsaSign(sign, hash, sizeof(hash), key);

		sign_data = NewBuf();
		WriteBuf(sign_data, sign, sizeof(sign));
		SeekBuf(sign_data, 0, 0);
	}

	b = NewBuf();

	WpcAddDataEntryBin(b, "PACK", pack_data->Buf, pack_data->Size);
	WpcAddDataEntryBin(b, "HASH", hash, sizeof(hash));

	if (cert_data != NULL)
	{
		WpcAddDataEntryBin(b, "CERT", cert_data->Buf, cert_data->Size);
		WpcAddDataEntryBin(b, "SIGN", sign_data->Buf, sign_data->Size);
	}

	FreeBuf(pack_data);
	FreeBuf(cert_data);
	FreeBuf(sign_data);

	SeekBuf(b, 0, 0);

	return b;
}