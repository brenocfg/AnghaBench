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
struct TYPE_2__ {scalar_t__ Status; char* filename; int ReadOnly; int /*<<< orphan*/ * fp; int /*<<< orphan*/  Size; } ;

/* Variables and functions */
 TYPE_1__ Movie ; 
 int /*<<< orphan*/  MovieGetSize (int /*<<< orphan*/ *) ; 
 char* MovieStatus ; 
 scalar_t__ Playback ; 
 int PlaybackFileOpened ; 
 int /*<<< orphan*/  ReadHeader (int /*<<< orphan*/ *) ; 
 scalar_t__ Recording ; 
 int /*<<< orphan*/  StopMovie () ; 
 int /*<<< orphan*/  YabauseReset () ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ framecounter ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

int PlayMovie(const char *filename) {

	char* str=malloc(1024);

	if(Movie.Status == Recording)
		StopMovie();


	if ((Movie.fp = fopen(filename, "r+b")) == NULL)
	{
		free(str);
		return -1;
	}

	strcpy(str, filename);
	Movie.filename=str;
	PlaybackFileOpened=1;
	framecounter=0;
	Movie.ReadOnly = 1;
	Movie.Status=Playback;
	Movie.Size = MovieGetSize(Movie.fp);
	strcpy(MovieStatus, "Playback Started");
	ReadHeader(Movie.fp);
	YabauseReset();
	return 0;
}