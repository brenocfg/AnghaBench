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
struct TYPE_2__ {scalar_t__ Status; char* filename; int /*<<< orphan*/ * fp; scalar_t__ Rerecords; } ;

/* Variables and functions */
 TYPE_1__ Movie ; 
 char* MovieStatus ; 
 scalar_t__ Playback ; 
 scalar_t__ Recording ; 
 int RecordingFileOpened ; 
 int /*<<< orphan*/  StopMovie () ; 
 int /*<<< orphan*/  WriteHeader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  YabauseReset () ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ framecounter ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

int SaveMovie(const char *filename) {

	char* str=malloc(1024);

	if(Movie.Status == Playback)
		StopMovie();

	if ((Movie.fp = fopen(filename, "w+b")) == NULL)
	{
		free(str);
		return -1;
	}

	strcpy(str, filename);
	Movie.filename=str;
	RecordingFileOpened=1;
	framecounter=0;
	Movie.Status=Recording;
	strcpy(MovieStatus, "Recording Started");
	Movie.Rerecords=0;
	WriteHeader(Movie.fp);
	YabauseReset();
	return 0;
}