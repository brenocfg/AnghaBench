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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  txt ;
typedef  int /*<<< orphan*/  tmp ;
typedef  size_t UINT ;
typedef  int UCHAR ;
struct TYPE_3__ {scalar_t__ type; } ;
typedef  TYPE_1__ ASN1_STRING ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 size_t CalcUtf8ToUni (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CopyUniStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EndianUnicode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OBJ_nid2obj (int) ; 
 int /*<<< orphan*/  StrLen (int*) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,char*) ; 
 int UniStrLen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Utf8ToUni (int /*<<< orphan*/ *,size_t,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ V_ASN1_BMPSTRING ; 
 scalar_t__ V_ASN1_T61STRING ; 
 scalar_t__ V_ASN1_UTF8STRING ; 
 TYPE_1__* X509_NAME_ENTRY_get_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_NAME_get_entry (void*,int) ; 
 int X509_NAME_get_index_by_OBJ (void*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ X509_NAME_get_text_by_NID (void*,int,char*,int) ; 
 int /*<<< orphan*/  Zero (int*,int) ; 
 int /*<<< orphan*/ * ZeroMalloc (size_t) ; 

wchar_t *GetUniStrFromX509Name(void *xn, int nid)
{
	UCHAR txt[1024];
	bool b = false;
	UINT i, size;
	int index;
	bool unicode = false;
	bool is_utf_8 = false;
	ASN1_OBJECT *obj;
	ASN1_STRING *data;
	// Validate arguments
	if (xn == NULL || nid == 0)
	{
		return NULL;
	}

	Zero(txt, sizeof(txt));
	if (X509_NAME_get_text_by_NID(xn, nid, (char *)txt, sizeof(txt) - 2) <= 0)
	{
		return NULL;
	}

	obj = OBJ_nid2obj(nid);
	if (obj == NULL)
	{
		return NULL;
	}
	index = X509_NAME_get_index_by_OBJ(xn, obj, -1);
	if (index < 0)
	{
		return NULL;
	}
	data = X509_NAME_ENTRY_get_data(X509_NAME_get_entry(xn, index));
	if (data == NULL)
	{
		return NULL;
	}
	if (data->type == V_ASN1_BMPSTRING)
	{
		unicode = true;
	}
	if (data->type == V_ASN1_UTF8STRING || data->type == V_ASN1_T61STRING)
	{
		is_utf_8 = true;
	}

	size = UniStrLen((wchar_t *)txt) * 4 + 8;
	for (i = 0;i < size;i++)
	{
		if (txt[i] >= 0x80)
		{
			unicode = true;
			break;
		}
	}

	if (is_utf_8)
	{
		wchar_t *ret;
		UINT ret_size;

		ret_size = CalcUtf8ToUni(txt, StrLen(txt));
		ret = ZeroMalloc(ret_size + 8);
		Utf8ToUni(ret, ret_size, txt, StrLen(txt));

		return ret;
	}
	else if (unicode == false)
	{
		wchar_t tmp[1024];
		StrToUni(tmp, sizeof(tmp), (char *)txt);
		return CopyUniStr(tmp);
	}
	else
	{
		EndianUnicode((wchar_t *)txt);
		return CopyUniStr((wchar_t *)txt);
	}
}