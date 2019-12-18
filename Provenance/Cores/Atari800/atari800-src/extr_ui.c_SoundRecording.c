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
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_2__ {int /*<<< orphan*/  (* fMessage ) (char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FilenameMessage (char*,char*) ; 
 int /*<<< orphan*/  SndSave_CloseSoundFile () ; 
 int /*<<< orphan*/  SndSave_IsSoundFileOpen () ; 
 scalar_t__ SndSave_OpenSoundFile (char*) ; 
 TYPE_1__* UI_driver ; 
 int /*<<< orphan*/  Util_fileexists (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  stub1 (char*,int) ; 
 int /*<<< orphan*/  stub2 (char*,int) ; 

__attribute__((used)) static void SoundRecording(void)
{
	if (!SndSave_IsSoundFileOpen()) {
		int no = 0;
		do {
			char buffer[32];
			snprintf(buffer, sizeof(buffer), "atari%03d.wav", no);
			if (!Util_fileexists(buffer)) {
				/* file does not exist - we can create it */
				FilenameMessage(SndSave_OpenSoundFile(buffer)
					? "Recording sound to file \"%s\""
					: "Can't write to file \"%s\"", buffer);
				return;
			}
		} while (++no < 1000);
		UI_driver->fMessage("All atariXXX.wav files exist!", 1);
	}
	else {
		SndSave_CloseSoundFile();
		UI_driver->fMessage("Recording stopped", 1);
	}
}