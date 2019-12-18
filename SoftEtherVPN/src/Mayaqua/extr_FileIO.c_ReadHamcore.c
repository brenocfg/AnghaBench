#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  exe_dir ;
typedef  scalar_t__ UINT ;
struct TYPE_6__ {char* FileName; void* Buffer; scalar_t__ Size; scalar_t__ LastAccess; int /*<<< orphan*/  SizeCompressed; int /*<<< orphan*/  Offset; } ;
typedef  TYPE_1__ HC ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int FileRead (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int FileSeek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (void*) ; 
 int /*<<< orphan*/  GetExeDirW (int /*<<< orphan*/ *,int) ; 
 scalar_t__ HAMCORE_CACHE_EXPIRES ; 
 int /*<<< orphan*/  HAMCORE_DIR_NAME ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int MAX_SIZE ; 
 void* Malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ MayaquaIsMinimalMode () ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/ * ReadDumpW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReplaceStrEx (char*,int,char*,char*,char*,int) ; 
 TYPE_1__* Search (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ StartWith (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 scalar_t__ Tick64 () ; 
 scalar_t__ Uncompress (void*,scalar_t__,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,void*,scalar_t__) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 void* ZeroMalloc (scalar_t__) ; 
 int /*<<< orphan*/  hamcore ; 
 int /*<<< orphan*/  hamcore_io ; 

BUF *ReadHamcore(char *name)
{
	wchar_t tmp[MAX_SIZE];
	wchar_t exe_dir[MAX_SIZE];
	BUF *b;
	char filename[MAX_PATH];
	// Validate arguments
	if (name == NULL)
	{
		return NULL;
	}

	if (name[0] == '|')
	{
		name++;
	}

	if (name[0] == '/' || name[0] == '\\')
	{
		name++;
	}

	StrCpy(filename, sizeof(filename), name);

	ReplaceStrEx(filename, sizeof(filename), filename, "/", "\\", true);

	if (MayaquaIsMinimalMode())
	{
		return NULL;
	}

	// If the file exist in hamcore/ directory on the local disk, read it
	GetExeDirW(exe_dir, sizeof(exe_dir));

	UniFormat(tmp, sizeof(tmp), L"%s/%S/%S", exe_dir, HAMCORE_DIR_NAME, filename);

	b = ReadDumpW(tmp);
	if (b != NULL)
	{
		return b;
	}

	// Search from HamCore file system if it isn't found
	LockList(hamcore);
	{
		HC t, *c;
		UINT i;

		Zero(&t, sizeof(t));
		t.FileName = filename;
		c = Search(hamcore, &t);

		if (c == NULL)
		{
			// File does not exist
			b = NULL;
		}
		else
		{
			// File exists
			if (c->Buffer != NULL)
			{
				// It is already loaded
				b = NewBuf();
				WriteBuf(b, c->Buffer, c->Size);
				SeekBuf(b, 0, 0);
				c->LastAccess = Tick64();
			}
			else
			{
				// Read from a file is if it is not read
				if (FileSeek(hamcore_io, 0, c->Offset) == false)
				{
					// Failed to seek
					b = NULL;
				}
				else
				{
					// Read the compressed data
					void *data = Malloc(c->SizeCompressed);
					if (FileRead(hamcore_io, data, c->SizeCompressed) == false)
					{
						// Failed to read
						Free(data);
						b = NULL;
					}
					else
					{
						// Expand
						c->Buffer = ZeroMalloc(c->Size);
						if (Uncompress(c->Buffer, c->Size, data, c->SizeCompressed) != c->Size)
						{
							// Failed to expand
							Free(data);
							Free(c->Buffer);
							b = NULL;
						}
						else
						{
							// Successful
							Free(data);
							b = NewBuf();
							WriteBuf(b, c->Buffer, c->Size);
							SeekBuf(b, 0, 0);
							c->LastAccess = Tick64();
						}
					}
				}
			}
		}

		// Delete the expired cache
		for (i = 0;i < LIST_NUM(hamcore);i++)
		{
			HC *c = LIST_DATA(hamcore, i);

			if (c->Buffer != NULL)
			{
				if (((c->LastAccess + HAMCORE_CACHE_EXPIRES) <= Tick64()) ||
					(StartWith(c->FileName, "Li")))
				{
					Free(c->Buffer);
					c->Buffer = NULL;
				}
			}
		}
	}
	UnlockList(hamcore);

	return b;
}