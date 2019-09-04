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
typedef  int USHORT ;
typedef  int UINT ;
struct TYPE_6__ {int Size; int* Buf; } ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 TYPE_1__* BuildDnsHostName (char*) ; 
 int Endian16 (int) ; 
 int Endian32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 int /*<<< orphan*/  NAT_DNS_RESPONSE_TTL ; 
 int /*<<< orphan*/  WriteBuf (TYPE_1__*,int*,int) ; 

void BuildDnsResponsePacketPtr(BUF *b, char *hostname)
{
	USHORT magic;
	USHORT type, clas;
	UINT ttl;
	USHORT len;
	BUF *c;
	// Validate arguments
	if (b == NULL || hostname == NULL)
	{
		return;
	}

	magic = Endian16(0xc00c);
	type = Endian16(0x000c);
	clas = Endian16(0x0001);
	ttl = Endian32(NAT_DNS_RESPONSE_TTL);

	c = BuildDnsHostName(hostname);
	if (c == NULL)
	{
		return;
	}
	len = Endian16((USHORT)c->Size);

	WriteBuf(b, &magic, 2);
	WriteBuf(b, &type, 2);
	WriteBuf(b, &clas, 2);
	WriteBuf(b, &ttl, 4);
	WriteBuf(b, &len, 2);
	WriteBuf(b, c->Buf, c->Size);
	FreeBuf(c);
}