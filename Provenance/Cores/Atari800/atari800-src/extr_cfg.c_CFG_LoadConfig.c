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
typedef  int /*<<< orphan*/  string ;
struct TYPE_2__ {int channels; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ AF80_ReadConfig (char*,char*) ; 
 scalar_t__ ARTIFACT_ReadConfig (char*,char*) ; 
 int /*<<< orphan*/  Atari800_MACHINE_5200 ; 
 int /*<<< orphan*/  Atari800_MACHINE_800 ; 
 int /*<<< orphan*/  Atari800_MACHINE_XLXE ; 
 int /*<<< orphan*/  Atari800_TV_NTSC ; 
 int /*<<< orphan*/  Atari800_TV_PAL ; 
 void* Atari800_builtin_basic ; 
 void* Atari800_builtin_game ; 
 void* Atari800_disable_basic ; 
 void* Atari800_f_keys ; 
 void* Atari800_jumper ; 
 void* Atari800_keyboard_detached ; 
 void* Atari800_keyboard_leds ; 
 int /*<<< orphan*/  Atari800_machine_type ; 
 void* Atari800_refresh_rate ; 
 int /*<<< orphan*/  Atari800_tv_mode ; 
 scalar_t__ CARTRIDGE_ReadConfig (char*,char*) ; 
 scalar_t__ CASSETTE_ReadConfig (char*,char*) ; 
 void* CFG_save_on_exit ; 
 scalar_t__ Colours_ReadConfig (char*,char*) ; 
 int /*<<< orphan*/  DEFAULT_CFG_NAME ; 
 int /*<<< orphan*/  Devices_SetPrintCommand (char*) ; 
 char** Devices_atari_h_dir ; 
 void* Devices_enable_h_patch ; 
 void* Devices_enable_p_patch ; 
 void* Devices_enable_r_patch ; 
 void* Devices_h_read_only ; 
 void* ESC_enable_sio_patch ; 
 int FALSE ; 
 int /*<<< orphan*/  FILENAME_MAX ; 
 scalar_t__ FILTER_NTSC_ReadConfig (char*,char*) ; 
 int /*<<< orphan*/  Log_print (char*,...) ; 
 int MEMORY_RAM_320_COMPY_SHOP ; 
 int MEMORY_RAM_320_RAMBO ; 
 scalar_t__ MEMORY_SizeValid (int) ; 
 int MEMORY_axlon_num_banks ; 
 void* MEMORY_enable_mapram ; 
 int MEMORY_mosaic_num_banks ; 
 int MEMORY_ram_size ; 
 scalar_t__ PBI_ReadConfig (char*,char*) ; 
 int /*<<< orphan*/  PLATFORM_ConfigInit () ; 
 int /*<<< orphan*/  PLATFORM_Configure (char*,char*) ; 
 void* POKEYSND_console_sound_enabled ; 
 void* POKEYSND_enable_new_pokey ; 
 void* POKEYSND_serio_sound_enabled ; 
 void* POKEYSND_stereo_enabled ; 
 scalar_t__ RTIME_ReadConfig (char*,char*) ; 
 scalar_t__ SYSROM_ReadConfig (char*,char*) ; 
 char* SYSTEM_WIDE_CFG_FILE ; 
 scalar_t__ Screen_ReadConfig (char*,char*) ; 
 scalar_t__ Sound_ReadConfig (char*,char*) ; 
 TYPE_1__ Sound_desired ; 
 int TRUE ; 
 scalar_t__ UI_MAX_DIRECTORIES ; 
 char** UI_atari_files_dir ; 
 scalar_t__ UI_n_atari_files_dir ; 
 scalar_t__ UI_n_saved_files_dir ; 
 char** UI_saved_files_dir ; 
 int /*<<< orphan*/  Util_catpath (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Util_chomp (char*) ; 
 void* Util_sscanbool (char*) ; 
 void* Util_sscandec (char*) ; 
 int /*<<< orphan*/  Util_strlcpy (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Util_trim (char*) ; 
 scalar_t__ VIDEOMODE_ReadConfig (char*,char*) ; 
 scalar_t__ XEP80_ReadConfig (char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 char* getenv (char*) ; 
 char* rtconfig_filename ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

int CFG_LoadConfig(const char *alternate_config_filename)
{
	FILE *fp;
	const char *fname = rtconfig_filename;
	char string[256];
#ifndef BASIC
	int was_obsolete_dir = FALSE;
#endif

#ifdef SUPPORTS_PLATFORM_CONFIGINIT
	PLATFORM_ConfigInit();
#endif

	/* if alternate config filename is passed then use it */
	if (alternate_config_filename != NULL && *alternate_config_filename > 0) {
		Util_strlcpy(rtconfig_filename, alternate_config_filename, FILENAME_MAX);
	}
	/* else use the default config name under the HOME folder */
	else {
		char *home = getenv("HOME");
		if (home != NULL)
			Util_catpath(rtconfig_filename, home, DEFAULT_CFG_NAME);
		else
			strcpy(rtconfig_filename, DEFAULT_CFG_NAME);
	}

	fp = fopen(fname, "r");
	if (fp == NULL) {
		Log_print("User config file '%s' not found.", rtconfig_filename);

#ifdef SYSTEM_WIDE_CFG_FILE
		/* try system wide config file */
		fname = SYSTEM_WIDE_CFG_FILE;
		Log_print("Trying system wide config file: %s", fname);
		fp = fopen(fname, "r");
#endif
		if (fp == NULL) {
			Log_print("No configuration file found, will create fresh one from scratch:");
			return FALSE;
		}
	}

	if (fgets(string, sizeof(string), fp) != NULL) {
		Log_print("Using Atari800 config file: %s\nCreated by %s", fname, string);
	}

	while (fgets(string, sizeof(string), fp)) {
		char *ptr;
		Util_chomp(string);
		ptr = strchr(string, '=');
		if (ptr != NULL) {
			*ptr++ = '\0';
			Util_trim(string);
			Util_trim(ptr);

			if (SYSROM_ReadConfig(string, ptr)) {
			}
#ifdef BASIC
			else if (strcmp(string, "ATARI_FILES_DIR") == 0
				  || strcmp(string, "SAVED_FILES_DIR") == 0
				  || strcmp(string, "DISK_DIR") == 0 || strcmp(string, "ROM_DIR") == 0
				  || strcmp(string, "EXE_DIR") == 0 || strcmp(string, "STATE_DIR") == 0)
				/* do nothing */;
#else
			else if (strcmp(string, "ATARI_FILES_DIR") == 0) {
				if (UI_n_atari_files_dir >= UI_MAX_DIRECTORIES)
					Log_print("All ATARI_FILES_DIR slots used!");
				else
					Util_strlcpy(UI_atari_files_dir[UI_n_atari_files_dir++], ptr, FILENAME_MAX);
			}
			else if (strcmp(string, "SAVED_FILES_DIR") == 0) {
				if (UI_n_saved_files_dir >= UI_MAX_DIRECTORIES)
					Log_print("All SAVED_FILES_DIR slots used!");
				else
					Util_strlcpy(UI_saved_files_dir[UI_n_saved_files_dir++], ptr, FILENAME_MAX);
			}
			else if (strcmp(string, "DISK_DIR") == 0 || strcmp(string, "ROM_DIR") == 0
				  || strcmp(string, "EXE_DIR") == 0 || strcmp(string, "STATE_DIR") == 0) {
				/* ignore blank and "." values */
				if (ptr[0] != '\0' && (ptr[0] != '.' || ptr[1] != '\0'))
					was_obsolete_dir = TRUE;
			}
#endif
			else if (strcmp(string, "H1_DIR") == 0)
				Util_strlcpy(Devices_atari_h_dir[0], ptr, FILENAME_MAX);
			else if (strcmp(string, "H2_DIR") == 0)
				Util_strlcpy(Devices_atari_h_dir[1], ptr, FILENAME_MAX);
			else if (strcmp(string, "H3_DIR") == 0)
				Util_strlcpy(Devices_atari_h_dir[2], ptr, FILENAME_MAX);
			else if (strcmp(string, "H4_DIR") == 0)
				Util_strlcpy(Devices_atari_h_dir[3], ptr, FILENAME_MAX);
			else if (strcmp(string, "HD_READ_ONLY") == 0)
				Devices_h_read_only = Util_sscandec(ptr);

			else if (strcmp(string, "PRINT_COMMAND") == 0) {
				if (!Devices_SetPrintCommand(ptr))
					Log_print("Unsafe PRINT_COMMAND ignored");
			}

			else if (strcmp(string, "SCREEN_REFRESH_RATIO") == 0)
				Atari800_refresh_rate = Util_sscandec(ptr);
			else if (strcmp(string, "DISABLE_BASIC") == 0)
				Atari800_disable_basic = Util_sscanbool(ptr);

			else if (strcmp(string, "ENABLE_SIO_PATCH") == 0) {
				ESC_enable_sio_patch = Util_sscanbool(ptr);
			}
			else if (strcmp(string, "ENABLE_H_PATCH") == 0) {
				Devices_enable_h_patch = Util_sscanbool(ptr);
			}
			else if (strcmp(string, "ENABLE_P_PATCH") == 0) {
				Devices_enable_p_patch = Util_sscanbool(ptr);
			}
			else if (strcmp(string, "ENABLE_R_PATCH") == 0) {
				Devices_enable_r_patch = Util_sscanbool(ptr);
			}

			else if (strcmp(string, "ENABLE_NEW_POKEY") == 0) {
#ifdef SOUND
				POKEYSND_enable_new_pokey = Util_sscanbool(ptr);
#endif /* SOUND */
			}
			else if (strcmp(string, "STEREO_POKEY") == 0) {
#ifdef STEREO_SOUND
				POKEYSND_stereo_enabled = Util_sscanbool(ptr);
#ifdef SOUND_THIN_API
				Sound_desired.channels = POKEYSND_stereo_enabled ? 2 : 1;
#endif /* SOUND_THIN_API */
#endif /* STEREO_SOUND */
			}
			else if (strcmp(string, "SPEAKER_SOUND") == 0) {
#ifdef CONSOLE_SOUND
				POKEYSND_console_sound_enabled = Util_sscanbool(ptr);
#endif
			}
			else if (strcmp(string, "SERIO_SOUND") == 0) {
#ifdef SERIO_SOUND
				POKEYSND_serio_sound_enabled = Util_sscanbool(ptr);
#endif
			}
			else if (strcmp(string, "MACHINE_TYPE") == 0) {
				if (strcmp(ptr, "Atari 400/800") == 0 ||
				    /* Also recognise legacy values of this parameter */
				    strcmp(ptr, "Atari OS/A") == 0 ||
				    strcmp(ptr, "Atari OS/B") == 0)
					Atari800_machine_type = Atari800_MACHINE_800;
				else if (strcmp(ptr, "Atari XL/XE") == 0)
					Atari800_machine_type = Atari800_MACHINE_XLXE;
				else if (strcmp(ptr, "Atari 5200") == 0)
					Atari800_machine_type = Atari800_MACHINE_5200;
				else
					Log_print("Invalid machine type: %s", ptr);
			}
			else if (strcmp(string, "RAM_SIZE") == 0) {
				if (strcmp(ptr, "320 (RAMBO)") == 0)
					MEMORY_ram_size = MEMORY_RAM_320_RAMBO;
				else if (strcmp(ptr, "320 (COMPY SHOP)") == 0)
					MEMORY_ram_size = MEMORY_RAM_320_COMPY_SHOP;
				else {
					int size = Util_sscandec(ptr);
					if (MEMORY_SizeValid(size))
						MEMORY_ram_size = size;
					else
						Log_print("Invalid RAM size: %s", ptr);
				}
			}
			else if (strcmp(string, "DEFAULT_TV_MODE") == 0) {
				if (strcmp(ptr, "PAL") == 0)
					Atari800_tv_mode = Atari800_TV_PAL;
				else if (strcmp(ptr, "NTSC") == 0)
					Atari800_tv_mode = Atari800_TV_NTSC;
				else
					Log_print("Invalid TV Mode: %s", ptr);
			}
			else if (strcmp(string, "MOSAIC_RAM_NUM_BANKS") == 0) {
				int num = Util_sscandec(ptr);
				if (num >= 0 && num <= 64)
					MEMORY_mosaic_num_banks = num;
				else
					Log_print("Invalid Mosaic RAM number of banks: %s", ptr);
			}
			else if (strcmp(string, "AXLON_RAM_NUM_BANKS") == 0) {
				int num = Util_sscandec(ptr);
				if (num == 0 || num == 8 || num == 16 || num == 32 || num == 64 || num == 128 || num == 256)
					MEMORY_axlon_num_banks = num;
				else
					Log_print("Invalid Mosaic RAM number of banks: %s", ptr);
			}
			else if (strcmp(string, "ENABLE_MAPRAM") == 0)
				MEMORY_enable_mapram = Util_sscanbool(ptr);
			else if (strcmp(string, "BUILTIN_BASIC") == 0)
				Atari800_builtin_basic = Util_sscanbool(ptr);
			else if (strcmp(string, "KEYBOARD_LEDS") == 0)
				Atari800_keyboard_leds = Util_sscanbool(ptr);
			else if (strcmp(string, "F_KEYS") == 0)
				Atari800_f_keys = Util_sscanbool(ptr);
			else if (strcmp(string, "BUILTIN_GAME") == 0)
				Atari800_builtin_game = Util_sscanbool(ptr);
			else if (strcmp(string, "KEYBOARD_DETACHED") == 0)
				Atari800_keyboard_detached = Util_sscanbool(ptr);
			else if (strcmp(string, "1200XL_JUMPER") == 0)
				Atari800_jumper = Util_sscanbool(ptr);
			else if (strcmp(string, "CFG_SAVE_ON_EXIT") == 0) {
				CFG_save_on_exit = Util_sscanbool(ptr);
			}
			/* Add module-specific configurations here */
			else if (PBI_ReadConfig(string,ptr)) {
			}
			else if (CARTRIDGE_ReadConfig(string, ptr)) {
			}
			else if (CASSETTE_ReadConfig(string, ptr)) {
			}
			else if (RTIME_ReadConfig(string, ptr)) {
			}
#ifdef XEP80_EMULATION
			else if (XEP80_ReadConfig(string, ptr)) {
			}
#endif
#ifdef AF80
			else if (AF80_ReadConfig(string,ptr)) {
			}
#endif
#if !defined(BASIC) && !defined(CURSES_BASIC)
			else if (Colours_ReadConfig(string, ptr)) {
			}
			else if (ARTIFACT_ReadConfig(string, ptr)) {
			}
			else if (Screen_ReadConfig(string, ptr)) {
			}
#endif
#ifdef NTSC_FILTER
			else if (FILTER_NTSC_ReadConfig(string, ptr)) {
			}
#endif
#if SUPPORTS_CHANGE_VIDEOMODE
			else if (VIDEOMODE_ReadConfig(string, ptr)) {
			}
#endif
#if defined(SOUND) && defined(SOUND_THIN_API)
			else if (Sound_ReadConfig(string, ptr)) {
			}
#endif /* defined(SOUND) && defined(SOUND_THIN_API) */
			else {
#ifdef SUPPORTS_PLATFORM_CONFIGURE
				if (!PLATFORM_Configure(string, ptr)) {
					Log_print("Unrecognized variable or bad parameters: '%s=%s'", string, ptr);
				}
#else
				Log_print("Unrecognized variable: %s", string);
#endif
			}
		}
		else {
			Log_print("Ignored config line: %s", string);
		}
	}

	fclose(fp);
#ifndef BASIC
	if (was_obsolete_dir) {
		Log_print(
			"DISK_DIR, ROM_DIR, EXE_DIR and STATE_DIR configuration options\n"
			"are no longer supported. Please use ATARI_FILES_DIR\n"
			"and SAVED_FILES_DIR in your Atari800 configuration file.");
	}
#endif
	return TRUE;
}