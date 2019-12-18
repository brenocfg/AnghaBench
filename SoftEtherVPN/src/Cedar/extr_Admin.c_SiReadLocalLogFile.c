#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  full_path ;
typedef  int /*<<< orphan*/  exe_dir ;
typedef  scalar_t__ UINT ;
struct TYPE_4__ {int /*<<< orphan*/  Buffer; } ;
typedef  int /*<<< orphan*/  SERVER ;
typedef  TYPE_1__ RPC_READ_LOG_FILE ;
typedef  int /*<<< orphan*/  IO ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_BEGIN ; 
 int /*<<< orphan*/  FTP_BLOCK_SIZE ; 
 int /*<<< orphan*/  FileClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FileOpenEx (char*,int,int) ; 
 int /*<<< orphan*/  FileRead (int /*<<< orphan*/ *,void*,scalar_t__) ; 
 int /*<<< orphan*/  FileSeek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ FileSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Format (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  Free (void*) ; 
 int /*<<< orphan*/  GetExeDir (char*,int) ; 
 int MAX_PATH ; 
 scalar_t__ MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewBuf () ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 void* ZeroMalloc (scalar_t__) ; 

void SiReadLocalLogFile(SERVER *s, char *filepath, UINT offset, RPC_READ_LOG_FILE *t)
{
	char exe_dir[MAX_PATH], full_path[MAX_PATH];
	IO *o;
	// Validate arguments
	if (s == NULL || t == NULL || filepath == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_READ_LOG_FILE));

	GetExeDir(exe_dir, sizeof(exe_dir));
	Format(full_path, sizeof(full_path), "%s/%s", exe_dir, filepath);

	// Read file
	o = FileOpenEx(full_path, false, false);
	if (o != NULL)
	{
		UINT filesize = FileSize(o);

		if (offset < filesize)
		{
			UINT readsize = MIN(filesize - offset, FTP_BLOCK_SIZE);
			void *buf = ZeroMalloc(readsize);

			FileSeek(o, FILE_BEGIN, offset);
			FileRead(o, buf, readsize);

			t->Buffer = NewBuf();
			WriteBuf(t->Buffer, buf, readsize);
			Free(buf);
		}

		FileClose(o);
	}
}