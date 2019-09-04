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
struct TYPE_3__ {int IntValue; int Size; int /*<<< orphan*/  UniStr; int /*<<< orphan*/ * Str; int /*<<< orphan*/ * Data; int /*<<< orphan*/  Int64Value; } ;
typedef  TYPE_1__ VALUE ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  CalcUniToUtf8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int StrLen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniToUtf8 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
#define  VALUE_DATA 132 
#define  VALUE_INT 131 
#define  VALUE_INT64 130 
#define  VALUE_STR 129 
#define  VALUE_UNISTR 128 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WriteBufInt (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WriteBufInt64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ZeroMalloc (int) ; 

void WriteValue(BUF *b, VALUE *v, UINT type)
{
	UINT len;
	BYTE *u;
	UINT u_size;
	// Validate arguments
	if (b == NULL || v == NULL)
	{
		return;
	}

	// Data item
	switch (type)
	{
	case VALUE_INT:			// Integer
		WriteBufInt(b, v->IntValue);
		break;
	case VALUE_INT64:		// 64 bit integer
		WriteBufInt64(b, v->Int64Value);
		break;
	case VALUE_DATA:		// Data
		// Size
		WriteBufInt(b, v->Size);
		// Body
		WriteBuf(b, v->Data, v->Size);
		break;
	case VALUE_STR:			// ANSI string
		len = StrLen(v->Str);
		// Length
		WriteBufInt(b, len);
		// String body
		WriteBuf(b, v->Str, len);
		break;
	case VALUE_UNISTR:		// Unicode string
		// Convert to UTF-8
		u_size = CalcUniToUtf8(v->UniStr) + 1;
		u = ZeroMalloc(u_size);
		UniToUtf8(u, u_size, v->UniStr);
		// Size
		WriteBufInt(b, u_size);
		// UTF-8 string body
		WriteBuf(b, u, u_size);
		Free(u);
		break;
	}
}