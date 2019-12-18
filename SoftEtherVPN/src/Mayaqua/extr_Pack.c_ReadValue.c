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
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  VALUE ;
typedef  int UINT ;
typedef  char BYTE ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int CalcUtf8ToUni (char*,int) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int MAX_VALUE_SIZE ; 
 void* Malloc (int) ; 
 int /*<<< orphan*/ * NewDataValue (void*,int) ; 
 int /*<<< orphan*/ * NewInt64Value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewIntValue (int) ; 
 int /*<<< orphan*/ * NewStrValue (char*) ; 
 int /*<<< orphan*/ * NewUniStrValue (char*) ; 
 int ReadBuf (int /*<<< orphan*/ *,char*,int) ; 
 int ReadBufInt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReadBufInt64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Utf8ToUni (char*,int,char*,int) ; 
#define  VALUE_DATA 132 
#define  VALUE_INT 131 
#define  VALUE_INT64 130 
#define  VALUE_STR 129 
#define  VALUE_UNISTR 128 
 char* ZeroMalloc (int /*<<< orphan*/ ) ; 

VALUE *ReadValue(BUF *b, UINT type)
{
	UINT len;
	BYTE *u;
	void *data;
	char *str;
	wchar_t *unistr;
	UINT unistr_size;
	UINT size;
	UINT u_size;
	VALUE *v = NULL;
	// Validate arguments
	if (b == NULL)
	{
		return NULL;
	}

	// Data item
	switch (type)
	{
	case VALUE_INT:			// Integer
		v = NewIntValue(ReadBufInt(b));
		break;
	case VALUE_INT64:
		v = NewInt64Value(ReadBufInt64(b));
		break;
	case VALUE_DATA:		// Data
		size = ReadBufInt(b);
		if (size > MAX_VALUE_SIZE)
		{
			// Size over
			break;
		}
		data = Malloc(size);
		if (ReadBuf(b, data, size) != size)
		{
			// Read failure
			Free(data);
			break;
		}
		v = NewDataValue(data, size);
		Free(data);
		break;
	case VALUE_STR:			// ANSI string
		len = ReadBufInt(b);
		if (len > (MAX_VALUE_SIZE - 1))
		{
			// Size over
			break;
		}
		str = Malloc(len + 1);
		// String body
		if (ReadBuf(b, str, len) != len)
		{
			// Read failure
			Free(str);
			break;
		}
		str[len] = 0;
		v = NewStrValue(str);
		Free(str);
		break;
	case VALUE_UNISTR:		// Unicode string
		u_size = ReadBufInt(b);
		if (u_size > MAX_VALUE_SIZE)
		{
			// Size over
			break;
		}
		// Reading an UTF-8 string
		u = ZeroMalloc(u_size + 1);
		if (ReadBuf(b, u, u_size) != u_size)
		{
			// Read failure
			Free(u);
			break;
		}
		// Convert to a Unicode string
		unistr_size = CalcUtf8ToUni(u, u_size);
		if (unistr_size == 0)
		{
			Free(u);
			break;
		}
		unistr = Malloc(unistr_size);
		Utf8ToUni(unistr, unistr_size, u, u_size);
		Free(u);
		v = NewUniStrValue(unistr);
		Free(unistr);
		break;
	}

	return v;
}