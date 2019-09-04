#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_9__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_8__ {int /*<<< orphan*/  SecureMode; } ;
typedef  TYPE_1__ SOCK ;
typedef  int /*<<< orphan*/  HTTP_HEADER ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  AddHttpValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 int /*<<< orphan*/ * GetHttpValue (int /*<<< orphan*/ *,char*) ; 
 char* HttpHeaderToStr (int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 TYPE_2__* NewBuf () ; 
 int /*<<< orphan*/  NewHttpValue (char*,char*) ; 
 int SendAll (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 int /*<<< orphan*/  ToStr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_2__*,void*,int /*<<< orphan*/ ) ; 

bool PostHttp(SOCK *s, HTTP_HEADER *header, void *post_data, UINT post_size)
{
	char *header_str;
	BUF *b;
	bool ret;
	// Validate arguments
	if (s == NULL || header == NULL || (post_size != 0 && post_data == NULL))
	{
		return false;
	}

	// Check whether the Content-Length exists?
	if (GetHttpValue(header, "Content-Length") == NULL)
	{
		char tmp[MAX_SIZE];
		// Add because it does not exist
		ToStr(tmp, post_size);
		AddHttpValue(header, NewHttpValue("Content-Length", tmp));
	}

	// Convert the header to string
	header_str = HttpHeaderToStr(header);
	if (header_str == NULL)
	{
		return false;
	}
	b = NewBuf();
	WriteBuf(b, header_str, StrLen(header_str));
	Free(header_str);

	// Append the data
	WriteBuf(b, post_data, post_size);

	// Send
	ret = SendAll(s, b->Buf, b->Size, s->SecureMode);

	FreeBuf(b);

	return ret;
}