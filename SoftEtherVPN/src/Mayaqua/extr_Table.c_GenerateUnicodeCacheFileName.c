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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  hashtemp ;
typedef  int /*<<< orphan*/  hashstr ;
typedef  int /*<<< orphan*/  exe ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  BinToStrW (char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GetExeDirW (char*,int) ; 
 int MAX_SIZE ; 
 int MD5_SIZE ; 
 int /*<<< orphan*/  MsGetTempDir () ; 
 int /*<<< orphan*/  NormalizePathW (char*,int /*<<< orphan*/ ,char*) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha0 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  StrToUni (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNICODE_CACHE_FILE ; 
 int /*<<< orphan*/  UniFormat (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  UniStrCat (char*,int,char*) ; 
 int /*<<< orphan*/  UniStrCpy (char*,int,char*) ; 
 int UniStrLen (char*) ; 
 int /*<<< orphan*/  UniStrLower (char*) ; 

void GenerateUnicodeCacheFileName(wchar_t *name, UINT size, wchar_t *strfilename, UINT strfilesize, UCHAR *filehash)
{
	wchar_t tmp[MAX_SIZE];
	wchar_t hashstr[64];
	wchar_t hashtemp[MAX_SIZE];
	wchar_t exe[MAX_SIZE];
	UCHAR hash[SHA1_SIZE];
	// Validate arguments
	if (name == NULL || strfilename == NULL || filehash == NULL)
	{
		return;
	}

	GetExeDirW(exe, sizeof(exe));
	UniStrCpy(hashtemp, sizeof(hashtemp), strfilename);
	BinToStrW(tmp, sizeof(tmp), filehash, MD5_SIZE);
	UniStrCat(hashtemp, sizeof(hashtemp), tmp);
	UniStrCat(hashtemp, sizeof(hashtemp), exe);
	UniStrLower(hashtemp);

	Sha0(hash, hashtemp, UniStrLen(hashtemp) * sizeof(wchar_t));
	BinToStrW(hashstr, sizeof(hashstr), hash, 4);
	UniFormat(tmp, sizeof(tmp), UNICODE_CACHE_FILE, hashstr);
	UniStrLower(tmp);

#ifndef	OS_WIN32
	UniStrCpy(exe, sizeof(exe), L"/tmp");
#else	// OS_WIN32
	StrToUni(exe, sizeof(exe), MsGetTempDir());
#endif	// OS_WIN32

	UniFormat(name, size, L"%s/%s", exe, tmp);
	NormalizePathW(name, size, name);
}