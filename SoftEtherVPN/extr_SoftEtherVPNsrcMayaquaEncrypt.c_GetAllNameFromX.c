#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp3 ;
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp1 ;
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_6__ {TYPE_1__* serial; int /*<<< orphan*/  subject_name; } ;
typedef  TYPE_2__ X ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_5__ {int size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BinToStr (char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GetAllNameFromName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetXDigest (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int MD5_SIZE ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,char*,char*,...) ; 
 int /*<<< orphan*/  UniStrCat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void GetAllNameFromX(wchar_t *str, UINT size, X *x)
{
	UCHAR md5[MD5_SIZE], sha1[SHA1_SIZE];
	char tmp1[MD5_SIZE * 3 + 8], tmp2[SHA1_SIZE * 3 + 8];
	wchar_t tmp3[sizeof(tmp1) + sizeof(tmp2) + 64];
	// Validate arguments
	if (str == NULL || x == NULL)
	{
		return;
	}

	GetAllNameFromName(str, size, x->subject_name);

	if (x->serial != NULL && x->serial->size >= 1)
	{
		char tmp[128];
		wchar_t tmp2[128];

		BinToStr(tmp, sizeof(tmp), x->serial->data, x->serial->size);
		UniFormat(tmp2, sizeof(tmp2), L", SERIAL=\"%S\"", tmp);

		UniStrCat(str, size, tmp2);
	}

	// Digest value
	GetXDigest(x, md5, false);
	GetXDigest(x, sha1, true);

	BinToStr(tmp1, sizeof(tmp1), md5, MD5_SIZE);
	BinToStr(tmp2, sizeof(tmp2), sha1, SHA1_SIZE);

	UniFormat(tmp3, sizeof(tmp3), L" (Digest: MD5=\"%S\", SHA1=\"%S\")", tmp1, tmp2);
	UniStrCat(str, size, tmp3);
}