#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ Status; int Frames; scalar_t__ ReadOnly; int /*<<< orphan*/  fp; } ;
struct TYPE_5__ {int /*<<< orphan*/ * data; } ;
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearInput () ; 
 int /*<<< orphan*/  IncrementLagAndFrameCounter () ; 
 int LagFrameFlag ; 
 TYPE_3__ Movie ; 
 int /*<<< orphan*/  MovieStatus ; 
 TYPE_2__ PORTDATA1 ; 
 TYPE_1__ PORTDATA2 ; 
 scalar_t__ Playback ; 
 scalar_t__ PlaybackFileOpened ; 
 scalar_t__ Recording ; 
 scalar_t__ RecordingFileOpened ; 
 int /*<<< orphan*/  SetInputDisplayCharacters () ; 
 void* Stopped ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int framelength ; 
 size_t fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int headersize ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

void DoMovie(void) {

	int x;
   size_t num_read = 0;

	if (Movie.Status == 0)
		return;

	IncrementLagAndFrameCounter();
	LagFrameFlag=1;
	SetInputDisplayCharacters();

	//Read/Write Controller Data
	if(Movie.Status == Recording) {
		for (x = 0; x < 8; x++) {
			fwrite(&PORTDATA1.data[x], 1, 1, Movie.fp);
		}
		for (x = 0; x < 8; x++) {
			fwrite(&PORTDATA2.data[x], 1, 1, Movie.fp);
		}
	}

	if(Movie.Status == Playback) {
		for (x = 0; x < 8; x++) {
         num_read = fread(&PORTDATA1.data[x], 1, 1, Movie.fp);
		}
		for (x = 0; x < 8; x++) {
         num_read = fread(&PORTDATA2.data[x], 1, 1, Movie.fp);
		}

		//if we get to the end of the movie
		if(((ftell(Movie.fp)-headersize)/framelength) >= Movie.Frames) {
			fclose(Movie.fp);
			PlaybackFileOpened=0;
			Movie.Status = Stopped;
			ClearInput();
			strcpy(MovieStatus, "Playback Stopped");
		}
	}

	//Stop Recording/Playback
	if(Movie.Status != Recording && RecordingFileOpened) {
		fclose(Movie.fp);
		RecordingFileOpened=0;
		Movie.Status = Stopped;
		strcpy(MovieStatus, "Recording Stopped");
	}

	if(Movie.Status != Playback && PlaybackFileOpened && Movie.ReadOnly != 0) {
		fclose(Movie.fp);
		PlaybackFileOpened=0;
		Movie.Status = Stopped;
		strcpy(MovieStatus, "Playback Stopped");
	}
}