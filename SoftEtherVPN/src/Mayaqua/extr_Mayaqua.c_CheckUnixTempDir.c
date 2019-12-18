#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp ;
typedef  char* UINT64 ;
struct TYPE_2__ {int /*<<< orphan*/  OsType; } ;
typedef  int /*<<< orphan*/  IO ;

/* Variables and functions */
 int /*<<< orphan*/  FileClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FileCreate (char*) ; 
 int /*<<< orphan*/  FileDelete (char*) ; 
 int /*<<< orphan*/ * FileOpen (char*,int) ; 
 int /*<<< orphan*/  Format (char*,int,char*,char*) ; 
 TYPE_1__* GetOsInfo () ; 
 int /*<<< orphan*/  MakeDir (char*) ; 
 scalar_t__ OS_IS_UNIX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Print (char*) ; 
 char* SystemTime64 () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 

void CheckUnixTempDir()
{
	if (OS_IS_UNIX(GetOsInfo()->OsType))
	{
		char tmp[128], tmp2[64];
		UINT64 now = SystemTime64();
		IO *o;

		MakeDir("/tmp");

		Format(tmp2, sizeof(tmp2), "%I64u", now);

		Format(tmp, sizeof(tmp), "/tmp/.%s", tmp2);

		o = FileCreate(tmp);
		if (o == NULL)
		{
			o = FileOpen(tmp, false);
			if (o == NULL)
			{
				Print("Unable to use /tmp.\n\n");
				exit(0);
			}
		}

		FileClose(o);

		FileDelete(tmp);
	}
}