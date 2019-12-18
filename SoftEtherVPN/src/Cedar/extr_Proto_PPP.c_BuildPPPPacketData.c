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
typedef  int USHORT ;
typedef  int UCHAR ;
struct TYPE_3__ {int* Data; int DataSize; int /*<<< orphan*/  Lcp; scalar_t__ IsControl; int /*<<< orphan*/  Protocol; } ;
typedef  TYPE_1__ PPP_PACKET ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * BuildLCPData (int /*<<< orphan*/ ) ; 
 int Endian16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  WriteBufBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BUF *BuildPPPPacketData(PPP_PACKET *pp)
{
	BUF *ret;
	UCHAR c;
	USHORT us;
	// Validate arguments
	if (pp == NULL)
	{
		return NULL;
	}

	ret = NewBuf();

	// Address
	c = 0xff;
	WriteBuf(ret, &c, 1);

	// Control
	c = 0x03;
	WriteBuf(ret, &c, 1);

	// Protocol
	us = Endian16(pp->Protocol);
	WriteBuf(ret, &us, 2);

	if (pp->IsControl)
	{
		// LCP
		BUF *b = BuildLCPData(pp->Lcp);

		WriteBufBuf(ret, b);

		FreeBuf(b);
	}
	else
	{
		// Data
		WriteBuf(ret, pp->Data, pp->DataSize);
	}

	SeekBuf(ret, 0, 0);

	return ret;
}