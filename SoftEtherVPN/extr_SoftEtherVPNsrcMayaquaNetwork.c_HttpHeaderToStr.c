#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_10__ {int Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_9__ {int /*<<< orphan*/  ValueList; int /*<<< orphan*/  Version; int /*<<< orphan*/  Target; int /*<<< orphan*/  Method; } ;
struct TYPE_8__ {int /*<<< orphan*/  Data; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ HTTP_VALUE ;
typedef  TYPE_2__ HTTP_HEADER ;
typedef  TYPE_3__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Format (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_3__*) ; 
 int HTTP_HEADER_LINE_MAX_SIZE ; 
 scalar_t__ LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 char* Malloc (int) ; 
 TYPE_3__* NewBuf () ; 
 int StrLen (char*) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_3__*,char*,int) ; 

char *HttpHeaderToStr(HTTP_HEADER *header)
{
	BUF *b;
	char *tmp;
	UINT i;
	char *s;
	// Validate arguments
	if (header == NULL)
	{
		return NULL;
	}

	tmp = Malloc(HTTP_HEADER_LINE_MAX_SIZE);
	b = NewBuf();

	// Header
	Format(tmp, HTTP_HEADER_LINE_MAX_SIZE,
		"%s %s %s\r\n", header->Method, header->Target, header->Version);
	WriteBuf(b, tmp, StrLen(tmp));

	// Value
	for (i = 0;i < LIST_NUM(header->ValueList);i++)
	{
		HTTP_VALUE *v = (HTTP_VALUE *)LIST_DATA(header->ValueList, i);
		Format(tmp, HTTP_HEADER_LINE_MAX_SIZE,
			"%s: %s\r\n", v->Name, v->Data);
		WriteBuf(b, tmp, StrLen(tmp));
	}

	// Trailing newline
	WriteBuf(b, "\r\n", 2);
	s = Malloc(b->Size + 1);
	Copy(s, b->Buf, b->Size);
	s[b->Size] = 0;

	FreeBuf(b);
	Free(tmp);

	return s;
}