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
typedef  int /*<<< orphan*/  size_str ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Format (char*,int,char*,int /*<<< orphan*/ ) ; 
 int WPC_DATA_ENTRY_SIZE ; 
 int /*<<< orphan*/  WpcFillEntryName (char*,char*) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,void*,int) ; 

void WpcAddDataEntry(BUF *b, char *name, void *data, UINT size)
{
	char entry_name[WPC_DATA_ENTRY_SIZE];
	char size_str[11];
	// Validate arguments
	if (b == NULL || name == NULL || (data == NULL && size != 0))
	{
		return;
	}

	WpcFillEntryName(entry_name, name);
	WriteBuf(b, entry_name, WPC_DATA_ENTRY_SIZE);

	Format(size_str, sizeof(size_str), "%010u", size);
	WriteBuf(b, size_str, 10);

	WriteBuf(b, data, size);
}