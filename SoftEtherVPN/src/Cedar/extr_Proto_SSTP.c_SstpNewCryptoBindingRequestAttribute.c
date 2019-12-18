#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UCHAR ;
struct TYPE_5__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
typedef  int /*<<< orphan*/  SSTP_ATTRIBUTE ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 TYPE_1__* NewBuf () ; 
 int /*<<< orphan*/  SSTP_ATTRIB_CRYPTO_BINDING_REQ ; 
 int SSTP_NONCE_SIZE ; 
 int /*<<< orphan*/ * SstpNewAttribute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_1__*,scalar_t__*,int) ; 

SSTP_ATTRIBUTE *SstpNewCryptoBindingRequestAttribute(UCHAR hash_protocol_bitmask, UCHAR *nonce_32bytes)
{
	SSTP_ATTRIBUTE *a;
	UCHAR uc;
	BUF *b = NewBuf();

	uc = 0;
	WriteBuf(b, &uc, 1);
	WriteBuf(b, &uc, 1);
	WriteBuf(b, &uc, 1);
	WriteBuf(b, &hash_protocol_bitmask, 1);

	WriteBuf(b, nonce_32bytes, SSTP_NONCE_SIZE);

	a = SstpNewAttribute(SSTP_ATTRIB_CRYPTO_BINDING_REQ, b->Buf, b->Size);

	FreeBuf(b);

	return a;
}