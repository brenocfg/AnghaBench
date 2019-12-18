#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ip_str ;
typedef  int /*<<< orphan*/  dtstr ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_9__ {int /*<<< orphan*/  Size; int /*<<< orphan*/ * Buf; } ;
struct TYPE_8__ {scalar_t__ num_value; int type; int JsonHint_IsIP; int JsonHint_IsDateTime; TYPE_1__** values; int /*<<< orphan*/  name; int /*<<< orphan*/  JsonHint_IsBool; } ;
struct TYPE_7__ {char* Str; char* UniStr; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  JSON_ARRAY ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_2__ ELEMENT ;
typedef  TYPE_3__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (TYPE_3__*) ; 
 int /*<<< orphan*/  IPToStr (char*,int,int /*<<< orphan*/ *) ; 
 int InStr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  JsonArrayAddBool (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JsonArrayAddData (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JsonArrayAddNumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JsonArrayAddStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  JsonArrayAddUniStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetBoolEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_3__* PackGetBufEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PackGetInt64Ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PackGetIntEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PackGetIpEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  SystemTime64ToJsonStr (char*,int,int /*<<< orphan*/ ) ; 
#define  VALUE_DATA 132 
#define  VALUE_INT 131 
#define  VALUE_INT64 130 
#define  VALUE_STR 129 
#define  VALUE_UNISTR 128 

void PackArrayElementToJsonArray(JSON_ARRAY *ja, PACK *p, ELEMENT *e, UINT index)
{
	if (ja == NULL || p == NULL || e == NULL || index >= e->num_value)
	{
		return;
	}

	switch (e->type)
	{
	case VALUE_INT:
		if (e->JsonHint_IsIP)
		{
			if (InStr(e->name, "@") == false)
			{
				IP ip;
				if (PackGetIpEx(p, e->name, &ip, index))
				{
					char ip_str[64];
					IPToStr(ip_str, sizeof(ip_str), &ip);
					JsonArrayAddStr(ja, ip_str);
				}
			}
		}
		else if (e->JsonHint_IsBool)
		{
			JsonArrayAddBool(ja, PackGetBoolEx(p, e->name, index));
		}
		else
		{
			JsonArrayAddNumber(ja, PackGetIntEx(p, e->name, index));
		}
		break;
	case VALUE_INT64:
		if (e->JsonHint_IsIP == false)
		{
			if (e->JsonHint_IsDateTime == false)
			{
				JsonArrayAddNumber(ja, PackGetInt64Ex(p, e->name, index));
			}
			else
			{
				char dtstr[64];

				SystemTime64ToJsonStr(dtstr, sizeof(dtstr), PackGetInt64Ex(p, e->name, index));
				JsonArrayAddStr(ja, dtstr);
			}
		}
		break;
	case VALUE_DATA:
		if (e->JsonHint_IsIP == false)
		{
			BUF *buf = PackGetBufEx(p, e->name, index);
			if (buf != NULL)
			{
				JsonArrayAddData(ja, buf->Buf, buf->Size);
				FreeBuf(buf);
			}
			else
			{
				UCHAR zero = 0;
				JsonArrayAddData(ja, &zero, 0);
			}
		}
		break;
	case VALUE_STR:
		if (e->JsonHint_IsIP == false)
		{
			if (e->values[index] != NULL)
			{
				JsonArrayAddStr(ja, e->values[index]->Str);
			}
			else
			{
				JsonArrayAddStr(ja, "");
			}
		}
		break;
	case VALUE_UNISTR:
		if (e->JsonHint_IsIP == false)
		{
			if (e->values[index] != NULL)
			{
				JsonArrayAddUniStr(ja, e->values[index]->UniStr);
			}
			else
			{
				JsonArrayAddUniStr(ja, L"");
			}
		}
		break;
	}
}