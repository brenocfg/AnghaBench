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
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  ip_str ;
typedef  int /*<<< orphan*/  dtstr ;
typedef  size_t UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_10__ {int /*<<< orphan*/  Size; int /*<<< orphan*/ * Buf; } ;
struct TYPE_9__ {int type; int JsonHint_IsIP; int JsonHint_IsDateTime; TYPE_1__** values; int /*<<< orphan*/  name; int /*<<< orphan*/  JsonHint_IsBool; } ;
struct TYPE_8__ {char* Str; char* UniStr; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  JSON_OBJECT ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_2__ ELEMENT ;
typedef  TYPE_3__ BUF ;

/* Variables and functions */
 char* DetermineJsonSuffixForPackElement (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_3__*) ; 
 int /*<<< orphan*/  IPToStr (char*,int,int /*<<< orphan*/ *) ; 
 int InStr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  JsonSetBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JsonSetData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JsonSetNumber (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JsonSetStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  JsonSetUniStr (int /*<<< orphan*/ *,char*,char*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  PackGetBoolEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 TYPE_3__* PackGetBufEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  PackGetInt64Ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  PackGetIntEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  PackGetIpEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  StrCat (char*,int,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemTime64ToJsonStr (char*,int,int /*<<< orphan*/ ) ; 
#define  VALUE_DATA 132 
#define  VALUE_INT 131 
#define  VALUE_INT64 130 
#define  VALUE_STR 129 
#define  VALUE_UNISTR 128 

void PackElementToJsonObject(JSON_OBJECT *o, PACK *p, ELEMENT *e, UINT index)
{
	char *suffix;
	char name[MAX_PATH];
	if (o == NULL || p == NULL || e == NULL)
	{
		return;
	}

	suffix = DetermineJsonSuffixForPackElement(e);

	if (suffix == NULL)
	{
		return;
	}

	StrCpy(name, sizeof(name), e->name);
	StrCat(name, sizeof(name), suffix);

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
					JsonSetStr(o, name, ip_str);
				}
			}
		}
		else if (e->JsonHint_IsBool)
		{
			JsonSetBool(o, name, PackGetBoolEx(p, e->name, index));
		}
		else
		{
			JsonSetNumber(o, name, PackGetIntEx(p, e->name, index));
		}
		break;
	case VALUE_INT64:
		if (e->JsonHint_IsIP == false)
		{
			if (e->JsonHint_IsDateTime == false)
			{
				JsonSetNumber(o, name, PackGetInt64Ex(p, e->name, index));
			}
			else
			{
				char dtstr[64];

				SystemTime64ToJsonStr(dtstr, sizeof(dtstr), PackGetInt64Ex(p, e->name, index));
				JsonSetStr(o, name, dtstr);
			}
		}
		break;
	case VALUE_DATA:
		if (e->JsonHint_IsIP == false)
		{
			BUF *buf = PackGetBufEx(p, e->name, index);
			if (buf != NULL)
			{
				JsonSetData(o, name, buf->Buf, buf->Size);
				FreeBuf(buf);
			}
			else
			{
				UCHAR zero = 0;
				JsonSetData(o, name, &zero, 0);
			}
		}
		break;
	case VALUE_STR:
		if (e->JsonHint_IsIP == false)
		{
			if (e->values[index] != NULL)
			{
				JsonSetStr(o, name, e->values[index]->Str);
			}
			else
			{
				JsonSetStr(o, name, "");
			}
		}
		break;
	case VALUE_UNISTR:
		if (e->JsonHint_IsIP == false)
		{
			if (e->values[index] != NULL)
			{
				JsonSetUniStr(o, name, e->values[index]->UniStr);
			}
			else
			{
				JsonSetUniStr(o, name, L"");
			}
		}
		break;
	}
}