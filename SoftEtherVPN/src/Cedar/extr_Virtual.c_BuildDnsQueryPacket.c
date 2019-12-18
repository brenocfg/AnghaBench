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
typedef  int /*<<< orphan*/  USHORT ;
struct TYPE_6__ {int Size; int /*<<< orphan*/ * Buf; } ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 TYPE_1__* BuildDnsHostName (char*) ; 
 int /*<<< orphan*/  Endian16 (int) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

void BuildDnsQueryPacket(BUF *b, char *hostname, bool ptr)
{
	USHORT val;
	BUF *c;
	// Validate arguments
	if (b == NULL || hostname == NULL)
	{
		return;
	}

	// Convert the host name to a buffer
	c = BuildDnsHostName(hostname);
	if (c == NULL)
	{
		return;
	}

	WriteBuf(b, c->Buf, c->Size);
	FreeBuf(c);

	// Type and class
	if (ptr == false)
	{
		val = Endian16(0x0001);
	}
	else
	{
		val = Endian16(0x000c);
	}
	WriteBuf(b, &val, 2);

	val = Endian16(0x0001);
	WriteBuf(b, &val, 2);
}