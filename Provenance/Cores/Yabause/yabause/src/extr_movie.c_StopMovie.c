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
struct TYPE_2__ {scalar_t__ Status; scalar_t__ ReadOnly; int /*<<< orphan*/  fp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearInput () ; 
 TYPE_1__ Movie ; 
 int /*<<< orphan*/  MovieStatus ; 
 scalar_t__ Playback ; 
 scalar_t__ PlaybackFileOpened ; 
 scalar_t__ Recording ; 
 scalar_t__ RecordingFileOpened ; 
 void* Stopped ; 
 int /*<<< orphan*/  WriteHeader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

void StopMovie(void) {

	if(Movie.Status == Recording && RecordingFileOpened) {
		WriteHeader(Movie.fp);
		fclose(Movie.fp);
		RecordingFileOpened=0;
		Movie.Status = Stopped;
		ClearInput();
		strcpy(MovieStatus, "Recording Stopped");
	}

	if(Movie.Status == Playback && PlaybackFileOpened && Movie.ReadOnly != 0) {
		fclose(Movie.fp);
		PlaybackFileOpened=0;
		Movie.Status = Stopped;
		ClearInput();
		strcpy(MovieStatus, "Playback Stopped");
	}
}