#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  newfile ;
typedef  int /*<<< orphan*/  header ;
typedef  int /*<<< orphan*/  hash1 ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_9__ {int Size; scalar_t__ Buf; } ;
typedef  int /*<<< orphan*/  IO ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * CfgBufBinToFolder (TYPE_1__*) ; 
 int /*<<< orphan*/ * CfgBufTextToFolder (TYPE_1__*) ; 
 scalar_t__ Cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FILE_BEGIN ; 
 int /*<<< orphan*/  FileClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FileDeleteW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FileOpenW (int /*<<< orphan*/ *,int) ; 
 scalar_t__ FileRead (int /*<<< orphan*/ *,void*,int) ; 
 scalar_t__ FileSeek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ FileSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (void*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 int MAX_SIZE ; 
 void* Malloc (int) ; 
 TYPE_1__* NewBuf () ; 
 int /*<<< orphan*/  ReadBuf (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  SeekBuf (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sha0 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * TAG_BINARY ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_1__*,void*,int) ; 

FOLDER *CfgReadW(wchar_t *name)
{
	wchar_t tmp[MAX_SIZE];
	wchar_t newfile[MAX_SIZE];
	BUF *b;
	IO *o;
	UINT size;
	void *buf;
	FOLDER *f;
	bool delete_new = false;
	bool binary_file = false;
	UCHAR header[8];
	bool has_eof = false;
	// Validate arguments
	if (name == NULL)
	{
		return NULL;
	}

	// Generate a new file name
	UniFormat(newfile, sizeof(newfile), L"%s.new", name);
	// Generate a temporary file name
	UniFormat(tmp, sizeof(tmp), L"%s.log", name);

	// Read the new file if it exists
	o = FileOpenW(newfile, false);
	if (o == NULL)
	{
		UINT size;
		// Read the temporary file
		o = FileOpenW(tmp, false);

		if (o != NULL)
		{
			// Check the EOF
			size = FileSize(o);
			if (size >= 2)
			{
				char c;

				if (FileSeek(o, FILE_BEGIN, size - 1) && FileRead(o, &c, 1) && c == 0x1A && FileSeek(o, FILE_BEGIN, 0))
				{
					// EOF ok
					has_eof = true;
				}
				else
				{
					// No EOF: file is corrupted
					FileClose(o);
					o = NULL;
				}
			}
		}
	}
	else
	{
		delete_new = true;
	}
	if (o == NULL)
	{
		// Read the original file if there is no temporary file
		o = FileOpenW(name, false);
	}
	else
	{
		// Read the original file too if the size of temporary file is 0
		if (FileSize(o) == 0)
		{
			FileClose(o);
			o = FileOpenW(name, false);
		}
	}
	if (o == NULL)
	{
		// Failed to read
		return NULL;
	}

	// Read into the buffer
	size = FileSize(o);
	if (has_eof)
	{
		// Ignore EOF
		size -= 1;
	}
	buf = Malloc(size);
	FileRead(o, buf, size);
	b = NewBuf();
	WriteBuf(b, buf, size);
	SeekBuf(b, 0, 0);

	// Close the file
	FileClose(o);

	if (delete_new)
	{
		// Delete the new file
		FileDeleteW(newfile);
	}

	// If the beginning 8 character of the buffer is "SEVPN_DB", it is binary file
	ReadBuf(b, header, sizeof(header));
	if (Cmp(header, TAG_BINARY, 8) == 0)
	{
		UCHAR hash1[SHA1_SIZE], hash2[SHA1_SIZE];
		binary_file = true;

		// Check the hash 
		ReadBuf(b, hash1, sizeof(hash1));

		Sha0(hash2, ((UCHAR *)b->Buf) + 8 + SHA1_SIZE, b->Size - 8 - SHA1_SIZE);

		if (Cmp(hash1, hash2, SHA1_SIZE) != 0)
		{
			// Corrupted file
			FreeBuf(b);
			return NULL;
		}
	}

	SeekBuf(b, 0, 0);

	if (binary_file)
	{
		SeekBuf(b, 8 + SHA1_SIZE, 0);
	}

	// Convert the buffer into a folder
	if (binary_file == false)
	{
		// Text mode
		f = CfgBufTextToFolder(b);
	}
	else
	{
		// Binary mode
		f = CfgBufBinToFolder(b);
	}

	// Memory release
	Free(buf);
	FreeBuf(b);

	FileDeleteW(newfile);

	return f;
}