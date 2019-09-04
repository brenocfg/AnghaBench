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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  X509_NAME ;
typedef  int UINT ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 int CalcUniToUtf8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (scalar_t__*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int MBSTRING_ASC ; 
 int MBSTRING_UTF8 ; 
 scalar_t__ StrLen (scalar_t__*) ; 
 scalar_t__ UniStrLen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniToUtf8 (scalar_t__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_NAME_add_entry_by_NID (int /*<<< orphan*/ *,int,int,scalar_t__*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__* ZeroMalloc (int) ; 
 int /*<<< orphan*/  openssl_lock ; 

bool AddX509Name(void *xn, int nid, wchar_t *str)
{
	X509_NAME *x509_name;
	UINT utf8_size;
	BYTE *utf8;
	int encoding_type = MBSTRING_ASC;
	// Validate arguments
	if (xn == NULL || str == NULL)
	{
		return false;
	}

	// Convert to UTF-8
	utf8_size = CalcUniToUtf8(str);
	if (utf8_size == 0)
	{
		return false;
	}
	utf8 = ZeroMalloc(utf8_size + 1);
	UniToUtf8(utf8, utf8_size, str);
	utf8[utf8_size] = 0;

	if (StrLen(utf8) != UniStrLen(str))
	{
		encoding_type = MBSTRING_UTF8;
	}

	// Adding
	x509_name = (X509_NAME *)xn;
	Lock(openssl_lock);
	{
		X509_NAME_add_entry_by_NID(x509_name, nid, encoding_type, utf8, utf8_size, -1, 0);
	}
	Unlock(openssl_lock);
	Free(utf8);

	return true;
}