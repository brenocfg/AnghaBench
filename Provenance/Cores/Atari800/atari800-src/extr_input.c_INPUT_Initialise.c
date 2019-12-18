#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ EVENT_RECORDING_VERSION ; 
 int FALSE ; 
 int /*<<< orphan*/  GZBUFSIZE ; 
 int /*<<< orphan*/  INPUT_CenterMousePointer () ; 
 scalar_t__ INPUT_MOUSE_AMIGA ; 
 scalar_t__ INPUT_MOUSE_GUN ; 
 scalar_t__ INPUT_MOUSE_JOY ; 
 scalar_t__ INPUT_MOUSE_KOALA ; 
 scalar_t__ INPUT_MOUSE_OFF ; 
 scalar_t__ INPUT_MOUSE_PAD ; 
 scalar_t__ INPUT_MOUSE_PEN ; 
 scalar_t__ INPUT_MOUSE_ST ; 
 scalar_t__ INPUT_MOUSE_TOUCH ; 
 scalar_t__ INPUT_MOUSE_TRAK ; 
 int INPUT_cx85 ; 
 int INPUT_direct_mouse ; 
 int INPUT_joy_multijoy ; 
 scalar_t__ INPUT_mouse_mode ; 
 int INPUT_mouse_port ; 
 int INPUT_mouse_speed ; 
 int /*<<< orphan*/  Log_print (char*,...) ; 
 int TRUE ; 
 int Util_sscandec (char*) ; 
 int cx85_port ; 
 int /*<<< orphan*/  gzbuf ; 
 int /*<<< orphan*/  gzclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gzgets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* gzopen (char*,char*) ; 
 int /*<<< orphan*/  gzprintf (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/ * playbackfp ; 
 int playingback ; 
 int /*<<< orphan*/ * recordfp ; 
 int recording ; 
 scalar_t__ recording_version ; 
 int sscanf (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 scalar_t__ strcmp (char*,char*) ; 

int INPUT_Initialise(int *argc, char *argv[])
{
	int i;
	int j;

	for (i = j = 1; i < *argc; i++) {
		int i_a = (i + 1 < *argc);		/* is argument available? */
		int a_m = FALSE;			/* error, argument missing! */

		if (strcmp(argv[i], "-mouse") == 0) {
			if (i_a) {
				char *mode = argv[++i];
				if (strcmp(mode, "off") == 0)
					INPUT_mouse_mode = INPUT_MOUSE_OFF;
				else if (strcmp(mode, "pad") == 0)
					INPUT_mouse_mode = INPUT_MOUSE_PAD;
				else if (strcmp(mode, "touch") == 0)
					INPUT_mouse_mode = INPUT_MOUSE_TOUCH;
				else if (strcmp(mode, "koala") == 0)
					INPUT_mouse_mode = INPUT_MOUSE_KOALA;
				else if (strcmp(mode, "pen") == 0)
					INPUT_mouse_mode = INPUT_MOUSE_PEN;
				else if (strcmp(mode, "gun") == 0)
					INPUT_mouse_mode = INPUT_MOUSE_GUN;
				else if (strcmp(mode, "amiga") == 0)
					INPUT_mouse_mode = INPUT_MOUSE_AMIGA;
				else if (strcmp(mode, "st") == 0)
					INPUT_mouse_mode = INPUT_MOUSE_ST;
				else if (strcmp(mode, "trak") == 0)
					INPUT_mouse_mode = INPUT_MOUSE_TRAK;
				else if (strcmp(mode, "joy") == 0)
					INPUT_mouse_mode = INPUT_MOUSE_JOY;
			}
			else a_m = TRUE;
		}
		else if (strcmp(argv[i], "-mouseport") == 0) {
			if (i_a) {
				INPUT_mouse_port = Util_sscandec(argv[++i]) - 1;
				if (INPUT_mouse_port < 0 || INPUT_mouse_port > 3) {
					Log_print("Invalid mouse port number - should be between 0 and 3");
					return FALSE;
				}
			}
			else a_m = TRUE;
		}
		else if (strcmp(argv[i], "-mousespeed") == 0) {
			if (i_a) {
				INPUT_mouse_speed = Util_sscandec(argv[++i]);
				if (INPUT_mouse_speed < 1 || INPUT_mouse_speed > 9) {
					Log_print("Invalid mouse speed - should be between 1 and 9");
					return FALSE;
				}
			}
			else a_m = TRUE;
		}
		else if (strcmp(argv[i], "-multijoy") == 0) {
			INPUT_joy_multijoy = 1;
		}
#ifdef EVENT_RECORDING
		else if (strcmp(argv[i], "-record") == 0) {
			if (i_a) {
				char *recfilename = argv[++i];
				if ((recordfp = gzopen(recfilename, "wb")) == NULL) {
					Log_print("Cannot open record file");
					return FALSE;
				}
				else {
					recording = TRUE;
					gzprintf(recordfp, "Atari800 event recording, version: %d\n", EVENT_RECORDING_VERSION);
				}
			}
			else a_m = TRUE;
		}
		else if (strcmp(argv[i], "-playback") == 0) {
			if (i_a) {
				char *pbfilename = argv[++i];
				if ((playbackfp = gzopen(pbfilename, "rb")) == NULL) {
					Log_print("Cannot open playback file");
					return FALSE;
				}
				else {
					playingback = TRUE;
					gzgets(playbackfp, gzbuf, GZBUFSIZE);
					if (sscanf(gzbuf, "Atari800 event recording, version: %d\n", &recording_version) != 1) {
						Log_print("Invalid playback file");
						playingback = FALSE;
						gzclose(playbackfp);
						return FALSE;
					}
					else if (recording_version > EVENT_RECORDING_VERSION) {
						Log_print("Newer version of playback file than this version of Atari800 can handle");
						playingback = FALSE;
						gzclose(playbackfp);
						return FALSE;
					}
				}
			}
			else a_m = TRUE;
		}
#endif /* EVENT_RECORDING */
 		else if (strcmp(argv[i], "-directmouse") == 0) {
			INPUT_direct_mouse = 1;
		}
		else if (strcmp(argv[i], "-cx85") == 0) {
			if (i_a) {
				INPUT_cx85 = 1;
				cx85_port = Util_sscandec(argv[++i]) - 1;
				if (cx85_port < 0 || cx85_port > 3) {
					Log_print("Invalid cx85 port - should be between 0 and 3");
					return FALSE;
				}
			}
			else a_m = TRUE;
		}
		else {
			if (strcmp(argv[i], "-help") == 0) {
				Log_print("\t-mouse off       Do not use mouse");
				Log_print("\t-mouse pad       Emulate paddles");
				Log_print("\t-mouse touch     Emulate Atari Touch Tablet");
				Log_print("\t-mouse koala     Emulate Koala Pad");
				Log_print("\t-mouse pen       Emulate Light Pen");
				Log_print("\t-mouse gun       Emulate Light Gun");
				Log_print("\t-mouse amiga     Emulate Amiga mouse");
				Log_print("\t-mouse st        Emulate Atari ST mouse");
				Log_print("\t-mouse trak      Emulate Atari Trak-Ball");
				Log_print("\t-mouse joy       Emulate joystick using mouse");
				Log_print("\t-mouseport <n>   Set mouse port 1-4 (default 1)");
				Log_print("\t-mousespeed <n>  Set mouse speed 1-9 (default 3)");
				Log_print("\t-directmouse     Use absolute X/Y mouse coords");
				Log_print("\t-cx85 <n>        Emulate CX85 numeric keypad on port <n>");
				Log_print("\t-multijoy        Emulate MultiJoy4 interface");
				Log_print("\t-record <file>   Record input to <file>");
				Log_print("\t-playback <file> Playback input from <file>");
			}
			argv[j++] = argv[i];
		}

		/* this is the end of the additional argument check */
		if (a_m) {
			Log_print("Missing argument for '%s'", argv[i]);
			return FALSE;
		}
	}

	if(INPUT_direct_mouse && !(
				INPUT_mouse_mode == INPUT_MOUSE_PAD ||
				INPUT_mouse_mode == INPUT_MOUSE_TOUCH ||
				INPUT_mouse_mode == INPUT_MOUSE_KOALA)) {
		Log_print("-directmouse only valid with -mouse pad|touch|koala");
		return FALSE;
	}

	INPUT_CenterMousePointer();
	*argc = j;

	return TRUE;
}