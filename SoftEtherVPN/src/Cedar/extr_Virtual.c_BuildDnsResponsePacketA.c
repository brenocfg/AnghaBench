#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  type ;
typedef  int /*<<< orphan*/  ttl ;
typedef  int /*<<< orphan*/  magic ;
typedef  int /*<<< orphan*/  len ;
typedef  int /*<<< orphan*/  ip_addr ;
typedef  int /*<<< orphan*/  clas ;
typedef  int USHORT ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  IP ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int Endian16 (int) ; 
 int Endian32 (int /*<<< orphan*/ ) ; 
 int IPToUINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NAT_DNS_RESPONSE_TTL ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,int*,int) ; 

void BuildDnsResponsePacketA(BUF *b, IP *ip)
{
	UINT ip_addr;
	USHORT magic;
	USHORT type, clas;
	UINT ttl;
	USHORT len;
	// Validate arguments
	if (b == NULL || ip == NULL)
	{
		return;
	}

	ip_addr = IPToUINT(ip);
	magic = Endian16(0xc00c);
	type = Endian16(0x0001);
	clas = Endian16(0x0001);
	ttl = Endian32(NAT_DNS_RESPONSE_TTL);
	len = Endian16((USHORT)sizeof(ttl));

	WriteBuf(b, &magic, sizeof(magic));
	WriteBuf(b, &type, sizeof(type));
	WriteBuf(b, &clas, sizeof(clas));
	WriteBuf(b, &ttl, sizeof(ttl));
	WriteBuf(b, &len, sizeof(len));
	WriteBuf(b, &ip_addr, sizeof(ip_addr));
}