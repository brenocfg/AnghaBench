#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int UCHAR ;
struct TYPE_3__ {int* Random1; int* Random2; int /*<<< orphan*/  PeerInfo; int /*<<< orphan*/  Password; int /*<<< orphan*/  Username; int /*<<< orphan*/  OptionString; } ;
typedef  TYPE_1__ OPENVPN_KEY_METHOD_2 ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  OvsWriteStringToBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  WriteBufInt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BUF *OvsBuildKeyMethod2(OPENVPN_KEY_METHOD_2 *d)
{
	BUF *b;
	UCHAR uc;
	// Validate arguments
	if (d == NULL)
	{
		return NULL;
	}

	b = NewBuf();

	// Reserved
	WriteBufInt(b, 0);

	// Method
	uc = 2;
	WriteBuf(b, &uc, sizeof(UCHAR));

	// Random1
	WriteBuf(b, d->Random1, sizeof(d->Random1));

	// Random2
	WriteBuf(b, d->Random2, sizeof(d->Random2));

	// Option String
	OvsWriteStringToBuf(b, d->OptionString, sizeof(d->OptionString));

	// Username
	OvsWriteStringToBuf(b, d->Username, sizeof(d->Username));

	// Password
	OvsWriteStringToBuf(b, d->Password, sizeof(d->Password));

	// PeerInfo
	OvsWriteStringToBuf(b, d->PeerInfo, sizeof(d->PeerInfo));

	return b;
}