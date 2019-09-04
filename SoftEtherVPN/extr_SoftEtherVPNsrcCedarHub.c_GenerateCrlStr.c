#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  uni ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  str ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_5__ {int /*<<< orphan*/  DigestSHA1; int /*<<< orphan*/  DigestMD5; TYPE_1__* Serial; int /*<<< orphan*/ * Name; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ CRL ;

/* Variables and functions */
 int /*<<< orphan*/  BinToStrEx (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* CopyUniStr (char*) ; 
 int /*<<< orphan*/  GetAllNameFromName (char*,int,int /*<<< orphan*/ *) ; 
 int IsZero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MD5_SIZE ; 
 int /*<<< orphan*/  SHA1_SIZE ; 
 int /*<<< orphan*/  StrToUni (char*,int,char*) ; 
 scalar_t__ UniEndWith (char*,char*) ; 
 int /*<<< orphan*/  UniStrCat (char*,int,char*) ; 
 int /*<<< orphan*/  UniStrCpy (char*,int,char*) ; 
 int UniStrLen (char*) ; 

wchar_t *GenerateCrlStr(CRL *crl)
{
	wchar_t tmp[2048];
	// Validate arguments
	if (crl == NULL)
	{
		return NULL;
	}

	UniStrCpy(tmp, sizeof(tmp), L"");

	if (crl->Name != NULL)
	{
		// Name information
		wchar_t name[MAX_SIZE];

		UniStrCat(tmp, sizeof(tmp), L"Subject=\"");

		GetAllNameFromName(name, sizeof(name), crl->Name);
		UniStrCat(tmp, sizeof(tmp), name);
		UniStrCat(tmp, sizeof(tmp), L"\", ");
	}

	if (crl->Serial != NULL)
	{
		// Serial information
		char str[128];
		wchar_t uni[128];

		BinToStrEx(str, sizeof(str), crl->Serial->data, crl->Serial->size);
		StrToUni(uni, sizeof(uni), str);
		UniStrCat(tmp, sizeof(tmp), L"Serial=\"");
		UniStrCat(tmp, sizeof(tmp), uni);
		UniStrCat(tmp, sizeof(tmp), L"\", ");
	}

	if (IsZero(crl->DigestMD5, MD5_SIZE) == false)
	{
		// MD5
		char str[128];
		wchar_t uni[128];

		BinToStrEx(str, sizeof(str), crl->DigestMD5, MD5_SIZE);
		StrToUni(uni, sizeof(uni), str);
		UniStrCat(tmp, sizeof(tmp), L"MD5=\"");
		UniStrCat(tmp, sizeof(tmp), uni);
		UniStrCat(tmp, sizeof(tmp), L"\", ");
	}

	if (IsZero(crl->DigestSHA1, SHA1_SIZE) == false)
	{
		// MD5
		char str[128];
		wchar_t uni[128];

		BinToStrEx(str, sizeof(str), crl->DigestSHA1, SHA1_SIZE);
		StrToUni(uni, sizeof(uni), str);
		UniStrCat(tmp, sizeof(tmp), L"SHA1=\"");
		UniStrCat(tmp, sizeof(tmp), uni);
		UniStrCat(tmp, sizeof(tmp), L"\", ");
	}

	if (UniEndWith(tmp, L", "))
	{
		tmp[UniStrLen(tmp) - 2] = 0;
	}

	return CopyUniStr(tmp);
}