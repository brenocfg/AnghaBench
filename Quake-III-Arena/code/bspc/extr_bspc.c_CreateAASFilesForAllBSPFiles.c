#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_mode; } ;
struct _stat {int dummy; } ;
struct TYPE_9__ {char* pakfile; char* origname; struct TYPE_9__* next; } ;
typedef  TYPE_1__ quakefile_t ;
struct TYPE_10__ {int gl_pathc; char** gl_pathv; } ;
typedef  TYPE_2__ glob_t ;
typedef  int /*<<< orphan*/  foldername ;
typedef  int /*<<< orphan*/  filter ;
struct TYPE_11__ {char* cFileName; } ;
typedef  TYPE_3__ WIN32_FIND_DATA ;
typedef  scalar_t__ HWND ;

/* Variables and functions */
 int /*<<< orphan*/  AppendPathSeperator (char*,int) ; 
 scalar_t__ FindFirstFile (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  FindNextFile (scalar_t__,TYPE_3__*) ; 
 TYPE_1__* FindQuakeFiles (char*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  Log_Print (char*,char*) ; 
 int S_IFDIR ; 
 int _MAX_PATH ; 
 int /*<<< orphan*/  _splitpath (char*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _stat (char*,struct stat*) ; 
 int /*<<< orphan*/  glob (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  globfree (TYPE_2__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  stricmp (char*,char*) ; 
 size_t strlen (char*) ; 

void CreateAASFilesForAllBSPFiles(char *quakepath)
{
#if defined(WIN32)|defined(_WIN32)
	WIN32_FIND_DATA filedata;
	HWND handle;
	struct _stat statbuf;
#else
	glob_t globbuf;
	struct stat statbuf;
	int j;
#endif
	int done;
	char filter[_MAX_PATH], bspfilter[_MAX_PATH], aasfilter[_MAX_PATH];
	char aasfile[_MAX_PATH], buf[_MAX_PATH], foldername[_MAX_PATH];
	quakefile_t *qf, *qf2, *files, *bspfiles, *aasfiles;

	strcpy(filter, quakepath);
	AppendPathSeperator(filter, sizeof(filter));
	strcat(filter, "*");

#if defined(WIN32)|defined(_WIN32)
	handle = FindFirstFile(filter, &filedata);
	done = (handle == INVALID_HANDLE_VALUE);
	while(!done)
	{
		_splitpath(filter, foldername, NULL, NULL, NULL);
		_splitpath(filter, NULL, &foldername[strlen(foldername)], NULL, NULL);
		AppendPathSeperator(foldername, _MAX_PATH);
		strcat(foldername, filedata.cFileName);
		_stat(foldername, &statbuf);
#else
	glob(filter, 0, NULL, &globbuf);
	for (j = 0; j < globbuf.gl_pathc; j++)
	{
		strcpy(foldername, globbuf.gl_pathv[j]);
		stat(foldername, &statbuf);
#endif
		//if it is a folder
		if (statbuf.st_mode & S_IFDIR)
		{
			//
			AppendPathSeperator(foldername, sizeof(foldername));
			//get all the bsp files
			strcpy(bspfilter, foldername);
			strcat(bspfilter, "maps/*.bsp");
			files = FindQuakeFiles(bspfilter);
			strcpy(bspfilter, foldername);
			strcat(bspfilter, "*.pk3/maps/*.bsp");
			bspfiles = FindQuakeFiles(bspfilter);
			for (qf = bspfiles; qf; qf = qf->next) if (!qf->next) break;
			if (qf) qf->next = files;
			else bspfiles = files;
			//get all the aas files
			strcpy(aasfilter, foldername);
			strcat(aasfilter, "maps/*.aas");
			files = FindQuakeFiles(aasfilter);
			strcpy(aasfilter, foldername);
			strcat(aasfilter, "*.pk3/maps/*.aas");
			aasfiles = FindQuakeFiles(aasfilter);
			for (qf = aasfiles; qf; qf = qf->next) if (!qf->next) break;
			if (qf) qf->next = files;
			else aasfiles = files;
			//
			for (qf = bspfiles; qf; qf = qf->next)
			{
				sprintf(aasfile, "%s/%s", qf->pakfile, qf->origname);
				Log_Print("found %s\n", aasfile);
				strcpy(&aasfile[strlen(aasfile)-strlen(".bsp")], ".aas");
				for (qf2 = aasfiles; qf2; qf2 = qf2->next)
				{
					sprintf(buf, "%s/%s", qf2->pakfile, qf2->origname);
					if (!stricmp(aasfile, buf))
					{
						Log_Print("found %s\n", buf);
						break;
					} //end if
				} //end for
			} //end for
		} //end if
#if defined(WIN32)|defined(_WIN32)
		//find the next file
		done = !FindNextFile(handle, &filedata);
	} //end while
#else
	} //end for
	globfree(&globbuf);
#endif
}