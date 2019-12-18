#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_14__ {int /*<<< orphan*/  Target; int /*<<< orphan*/  Method; } ;
struct TYPE_13__ {int /*<<< orphan*/  Data; } ;
struct TYPE_12__ {int /*<<< orphan*/  SecureMode; } ;
typedef  TYPE_1__ SOCK ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_2__ HTTP_VALUE ;
typedef  TYPE_3__ HTTP_HEADER ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * BufToPack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeHttpHeader (TYPE_3__*) ; 
 scalar_t__ GetContentLength (TYPE_3__*) ; 
 TYPE_2__* GetHttpValue (TYPE_3__*,char*) ; 
 char* HTTP_CONTENT_TYPE2 ; 
 scalar_t__ MAX_PACK_SIZE ; 
 int /*<<< orphan*/ * MallocEx (scalar_t__,int) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int RecvAll (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_3__* RecvHttpHeader (TYPE_1__*) ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

PACK *HttpClientRecv(SOCK *s)
{
	BUF *b;
	PACK *p;
	HTTP_HEADER *h;
	UINT size;
	UCHAR *tmp;
	HTTP_VALUE *v;
	// Validate arguments
	if (s == NULL)
	{
		return NULL;
	}

	h = RecvHttpHeader(s);
	if (h == NULL)
	{
		return NULL;
	}

	if (StrCmpi(h->Method, "HTTP/1.1") != 0 ||
		StrCmpi(h->Target, "200") != 0)
	{
		FreeHttpHeader(h);
		return NULL;
	}

	v = GetHttpValue(h, "Content-Type");
	if (v == NULL || StrCmpi(v->Data, HTTP_CONTENT_TYPE2) != 0)
	{
		FreeHttpHeader(h);
		return NULL;
	}

	size = GetContentLength(h);
	if (size == 0 || size > MAX_PACK_SIZE)
	{
		FreeHttpHeader(h);
		return NULL;
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

	return p;
}