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
typedef  int UINT ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  EncodeSafe64 (char*,void*,int) ; 
 int /*<<< orphan*/  Free (char*) ; 
 char* Malloc (int) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 int /*<<< orphan*/  WpcAddDataEntry (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 

void WpcAddDataEntryBin(BUF *b, char *name, void *data, UINT size)
{
	char *str;
	// Validate arguments
	if (b == NULL || name == NULL || (data == NULL && size != 0))
	{
		return;
	}

	str = Malloc(size * 2 + 64);

	EncodeSafe64(str, data, size);

	WpcAddDataEntry(b, name, str, StrLen(str));

	Free(str);
}