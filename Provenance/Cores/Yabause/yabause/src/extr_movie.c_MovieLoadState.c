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
struct TYPE_3__ {int ReadOnly; scalar_t__ Status; int /*<<< orphan*/  Rerecords; int /*<<< orphan*/  fp; } ;

/* Variables and functions */
 TYPE_1__ Movie ; 
 int /*<<< orphan*/  MovieStatus ; 
 scalar_t__ Playback ; 
 scalar_t__ Recording ; 
 int RecordingFileOpened ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TruncateMovie (TYPE_1__) ; 
 int framecounter ; 
 int framelength ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ headersize ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

void MovieLoadState(void) {


	if (Movie.ReadOnly == 1 && Movie.Status == Playback)  {
		//Movie.Status = Playback;
		fseek (Movie.fp,headersize+(framecounter * framelength),SEEK_SET);
	}

	if(Movie.Status == Recording) {
		fseek (Movie.fp,headersize+(framecounter * framelength),SEEK_SET);
		Movie.Rerecords++;
	}

	if(Movie.Status == Playback && Movie.ReadOnly == 0) {
		Movie.Status = Recording;
		RecordingFileOpened=1;
		strcpy(MovieStatus, "Recording Resumed");
		TruncateMovie(Movie);
		fseek (Movie.fp,headersize+(framecounter * framelength),SEEK_SET);
		Movie.Rerecords++;
	}
}