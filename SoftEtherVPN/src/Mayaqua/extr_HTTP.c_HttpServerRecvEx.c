#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_15__ {int /*<<< orphan*/  Version; int /*<<< orphan*/  Target; int /*<<< orphan*/  Method; } ;
struct TYPE_14__ {int /*<<< orphan*/  Data; } ;
struct TYPE_13__ {int /*<<< orphan*/  SecureMode; } ;
typedef  TYPE_1__ SOCK ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_2__ HTTP_VALUE ;
typedef  TYPE_3__ HTTP_HEADER ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * BufToPack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Debug (char*) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeHttpHeader (TYPE_3__*) ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 scalar_t__ GetContentLength (TYPE_3__*) ; 
 TYPE_2__* GetHttpValue (TYPE_3__*,char*) ; 
 char* HTTP_CONTENT_TYPE2 ; 
 scalar_t__ HTTP_PACK_MAX_SIZE ; 
 char* HTTP_VPN_TARGET ; 
 int HttpServerSend (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ MAX_NOOP_PER_SESSION ; 
 int /*<<< orphan*/ * MallocEx (scalar_t__,int) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * PackError (int /*<<< orphan*/ ) ; 
 scalar_t__ PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int RecvAll (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_3__* RecvHttpHeader (TYPE_1__*) ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

PACK *HttpServerRecvEx(SOCK *s, UINT max_data_size)
{
	BUF *b;
	PACK *p;
	HTTP_HEADER *h;
	UINT size;
	UCHAR *tmp;
	HTTP_VALUE *v;
	UINT num_noop = 0;
	if (max_data_size == 0) max_data_size = HTTP_PACK_MAX_SIZE;
	// Validate arguments
	if (s == NULL)
	{
		return NULL;
	}

START:
	h = RecvHttpHeader(s);
	if (h == NULL)
	{
		goto BAD_REQUEST;
	}

	if (StrCmpi(h->Method, "POST") != 0 ||
		StrCmpi(h->Target, HTTP_VPN_TARGET) != 0 ||
		StrCmpi(h->Version, "HTTP/1.1") != 0)
	{
		FreeHttpHeader(h);
		goto BAD_REQUEST;
	}

	v = GetHttpValue(h, "Content-Type");
	if (v == NULL || StrCmpi(v->Data, HTTP_CONTENT_TYPE2) != 0)
	{
		FreeHttpHeader(h);
		goto BAD_REQUEST;
	}

	size = GetContentLength(h);
	if (size == 0 || (size > max_data_size))
	{
		FreeHttpHeader(h);
		goto BAD_REQUEST;
	}

	tmp = MallocEx(size, true);
	if (RecvAll(s, tmp, size, s->SecureMode) == false)
	{
		Free(tmp);
		FreeHttpHeader(h);
		return NULL;
	}

	b = NewBuf();
	WriteBuf(b, tmp, size);
	Free(tmp);
	FreeHttpHeader(h);

	SeekBuf(b, 0, 0);
	p = BufToPack(b);
	FreeBuf(b);

	// Determine whether it's a NOOP
	if (PackGetInt(p, "noop") != 0)
	{
		Debug("recv: noop\n");
		FreePack(p);

		p = PackError(0);
		PackAddInt(p, "noop", 1);
		if (HttpServerSend(s, p) == false)
		{
			FreePack(p);
			return NULL;
		}

		FreePack(p);

		num_noop++;

		if (num_noop > MAX_NOOP_PER_SESSION)
		{
			return NULL;
		}

		goto START;
	}

	return p;

BAD_REQUEST:
	// Return an error
	return NULL;
}