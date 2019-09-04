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
typedef  int /*<<< orphan*/  tmp ;
typedef  scalar_t__ UCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  Err; } ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  TYPE_1__ CONNECTION ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_CONNECT_FAILED ; 
 int /*<<< orphan*/  ERR_DISCONNECTED ; 
 int /*<<< orphan*/  ERR_PROXY_AUTH_FAILED ; 
 int /*<<< orphan*/  ERR_PROXY_ERROR ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  ReadBuf (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int RecvAll (int /*<<< orphan*/ *,scalar_t__*,int,int) ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,scalar_t__*,int) ; 

bool SocksRecvResponsePacket(CONNECTION *c, SOCK *s)
{
	BUF *b;
	UCHAR tmp[8];
	UCHAR vn, cd;
	// Validate arguments
	if (c == NULL || s == NULL)
	{
		return false;
	}

	if (RecvAll(s, tmp, sizeof(tmp), false) == false)
	{
		c->Err = ERR_DISCONNECTED;
		return false;
	}

	b = NewBuf();
	WriteBuf(b, tmp, sizeof(tmp));
	SeekBuf(b, 0, 0);

	ReadBuf(b, &vn, 1);
	ReadBuf(b, &cd, 1);

	FreeBuf(b);

	if (vn != 0)
	{
		c->Err = ERR_PROXY_ERROR;
		return false;
	}

	switch (cd)
	{
	case 90:
		// Success
		return true;

	case 93:
		// Authentication failure
		c->Err = ERR_PROXY_AUTH_FAILED;
		return false;

	default:
		// Connection to the server failure
		c->Err = ERR_CONNECT_FAILED;
		return false;
	}
}