#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char USHORT ;
typedef  scalar_t__ UINT ;
typedef  char UCHAR ;
struct TYPE_8__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_7__ {int /*<<< orphan*/  Err; } ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_1__ CONNECTION ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_DISCONNECTED ; 
 char Endian16 (char) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 scalar_t__ IPToUINT (int /*<<< orphan*/ *) ; 
 TYPE_2__* NewBuf () ; 
 int SendAll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int StrLen (char*) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_2__*,...) ; 

bool SocksSendRequestPacket(CONNECTION *c, SOCK *s, UINT dest_port, IP *dest_ip, char *userid)
{
	BUF *b;
	UCHAR vn, cd;
	USHORT port;
	UINT ip;
	bool ret;
	// Validate arguments
	if (s == NULL || dest_port == 0 || dest_ip == NULL || c == NULL)
	{
		return false;
	}
	if (userid == NULL)
	{
		userid = "";
	}

	b = NewBuf();
	vn = 4;
	cd = 1;
	WriteBuf(b, &vn, 1);
	WriteBuf(b, &cd, 1);
	port = Endian16((USHORT)dest_port);
	ip = IPToUINT(dest_ip);
	WriteBuf(b, &port, 2);
	WriteBuf(b, &ip, 4);
	WriteBuf(b, userid, StrLen(userid) + 1);

	ret = SendAll(s, b->Buf, b->Size, false);
	if (ret == false)
	{
		c->Err = ERR_DISCONNECTED;
	}

	FreeBuf(b);

	return ret;
}