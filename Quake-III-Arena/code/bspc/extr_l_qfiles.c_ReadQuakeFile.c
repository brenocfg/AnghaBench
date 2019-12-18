#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ unz_s ;
typedef  scalar_t__ unzFile ;
typedef  int /*<<< orphan*/  tmpbuf ;
struct TYPE_9__ {int /*<<< orphan*/  file; } ;
struct TYPE_8__ {int offset; int /*<<< orphan*/  filename; TYPE_3__ zipinfo; int /*<<< orphan*/  pakfile; scalar_t__ zipfile; } ;
typedef  TYPE_2__ quakefile_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/ * SafeOpenRead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SafeRead (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unzClose (scalar_t__) ; 
 int /*<<< orphan*/  unzCloseCurrentFile (TYPE_3__*) ; 
 scalar_t__ unzOpen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unzOpenCurrentFile (TYPE_3__*) ; 
 int unzReadCurrentFile (TYPE_3__*,void*,int) ; 

int ReadQuakeFile(quakefile_t *qf, void *buffer, int offset, int length)
{
	FILE *fp;
	int read;
	unzFile zf;
	char tmpbuf[1024];

	if (qf->zipfile)
	{
		//open the zip file
		zf = unzOpen(qf->pakfile);
		//set the file pointer
		qf->zipinfo.file = ((unz_s *) zf)->file;
		//open the Quake file in the zip file
		unzOpenCurrentFile(&qf->zipinfo);
		//
		while(offset > 0)
		{
			read = offset;
			if (read > sizeof(tmpbuf)) read = sizeof(tmpbuf);
			unzReadCurrentFile(&qf->zipinfo, tmpbuf, read);
			offset -= read;
		} //end while
		//read the Quake file from the zip file
		length = unzReadCurrentFile(&qf->zipinfo, buffer, length);
		//close the Quake file in the zip file
		unzCloseCurrentFile(&qf->zipinfo);
		//close the zip file
		unzClose(zf);

		return length;
	} //end if
	else
	{
		fp = SafeOpenRead(qf->filename);
		if (qf->offset) fseek(fp, qf->offset, SEEK_SET);
		if (offset) fseek(fp, offset, SEEK_CUR);
		SafeRead(fp, buffer, length);
		fclose(fp);

		return length;
	} //end else
}