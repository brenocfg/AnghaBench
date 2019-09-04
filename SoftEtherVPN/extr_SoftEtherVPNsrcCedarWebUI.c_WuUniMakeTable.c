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
typedef  scalar_t__ wchar_t ;
typedef  int UINT ;
struct TYPE_3__ {char* Name; int /*<<< orphan*/  Value; } ;
typedef  TYPE_1__ STRMAP_ENTRY ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int CalcUniToStr (scalar_t__*) ; 
 int /*<<< orphan*/  Free (scalar_t__*) ; 
 scalar_t__ Malloc (int) ; 
 int /*<<< orphan*/ * NewStrMap () ; 
 int /*<<< orphan*/  UniToStr (char*,int,scalar_t__*) ; 
 scalar_t__* WuUniCopyStrTill (scalar_t__*,int,scalar_t__**) ; 

__attribute__((used)) static LIST *WuUniMakeTable(wchar_t *def)
{
	LIST *table;
	STRMAP_ENTRY *entry;
	
	if(def==NULL)
	{
		return NULL;
	}

	table = NewStrMap();
	while(*def)
	{
		wchar_t *keytmp;
		UINT keylen;
		entry = (STRMAP_ENTRY*)Malloc(sizeof(STRMAP_ENTRY));
		def = WuUniCopyStrTill(def, L':', &keytmp);
		keylen = CalcUniToStr(keytmp);
		entry->Name = (char*)Malloc(keylen);
		UniToStr(entry->Name, keylen, keytmp);
		def = WuUniCopyStrTill(def, L',', (wchar_t**)&(entry->Value));
		Add(table, entry);
		Free(keytmp);
	}
	return table;
}