#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* filename; scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ CARTRIDGE_LAST_SUPPORTED ; 
 void* CARTRIDGE_NONE ; 
 void* CARTRIDGE_UNKNOWN ; 
 int CARTRIDGE_autoreboot ; 
 TYPE_1__ CARTRIDGE_main ; 
 TYPE_1__ CARTRIDGE_piggyback ; 
 scalar_t__ CartIsPassthrough (scalar_t__) ; 
 int FALSE ; 
 int /*<<< orphan*/  InitInsert (TYPE_1__*) ; 
 int /*<<< orphan*/  Log_print (char*,...) ; 
 int TRUE ; 
 int /*<<< orphan*/  Util_sscansdec (char*,scalar_t__*) ; 
 int /*<<< orphan*/  Util_strlcpy (char*,char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

int CARTRIDGE_Initialise(int *argc, char *argv[])
{
	int i;
	int j;
	int help_only = FALSE;
	/* When filename is given at commandline, we have to reset cartridge type to UNKNOWN,
	   because the cartridge type read earlier from the config file is no longer valid.
	   These two variables indicate that cartridge type is also given at commandline
	   and so it shouldn't be reset. */
	int type_from_commandline = FALSE;
	int type2_from_commandline = FALSE;

	for (i = j = 1; i < *argc; i++) {
		int i_a = (i + 1 < *argc); /* is argument available? */
		int a_m = FALSE; /* error, argument missing! */
		int a_i = FALSE; /* error, argument invalid! */
		
		if (strcmp(argv[i], "-cart") == 0) {
			if (i_a) {
				Util_strlcpy(CARTRIDGE_main.filename, argv[++i], sizeof(CARTRIDGE_main.filename));
				if (!type_from_commandline)
					CARTRIDGE_main.type = CARTRIDGE_UNKNOWN;
			}
			else a_m = TRUE;
		}
		else if (strcmp(argv[i], "-cart-type") == 0) {
			if (i_a) {
				Util_sscansdec(argv[++i], &CARTRIDGE_main.type);
				if (CARTRIDGE_main.type < 0 ||  CARTRIDGE_main.type > CARTRIDGE_LAST_SUPPORTED)
					a_i = TRUE;
				else
					type_from_commandline = TRUE;
			}
			else a_m = TRUE;
		}
		else if (strcmp(argv[i], "-cart2") == 0) {
			if (i_a) {
				Util_strlcpy(CARTRIDGE_piggyback.filename, argv[++i], sizeof(CARTRIDGE_piggyback.filename));
				if (!type2_from_commandline)
					CARTRIDGE_piggyback.type = CARTRIDGE_UNKNOWN;
			}
			else a_m = TRUE;
		}
		else if (strcmp(argv[i], "-cart2-type") == 0) {
			if (i_a) {
				Util_sscansdec(argv[++i], &CARTRIDGE_piggyback.type);
				if (CARTRIDGE_piggyback.type < 0 ||  CARTRIDGE_piggyback.type > CARTRIDGE_LAST_SUPPORTED)
					a_i = TRUE;
				else
					type2_from_commandline = TRUE;
			}
			else a_m = TRUE;
		}
		else if (strcmp(argv[i], "-cart-autoreboot") == 0)
			CARTRIDGE_autoreboot = TRUE;
		else if (strcmp(argv[i], "-no-cart-autoreboot") == 0)
			CARTRIDGE_autoreboot = FALSE;
		else {
			if (strcmp(argv[i], "-help") == 0) {
				help_only = TRUE;
				Log_print("\t-cart <file>         Install cartridge (raw or CART format)");
				Log_print("\t-cart-type <num>     Set cartridge type (0..%i)", CARTRIDGE_LAST_SUPPORTED);
				Log_print("\t-cart2 <file>        Install piggyback cartridge");
				Log_print("\t-cart2-type <num>    Set piggyback cartridge type (0..%i)", CARTRIDGE_LAST_SUPPORTED);
				Log_print("\t-cart-autoreboot     Reboot when cartridge is inserted/removed");
				Log_print("\t-no-cart-autoreboot  Don't reboot after changing cartridge");
			}
			argv[j++] = argv[i];
		}

		if (a_m) {
			Log_print("Missing argument for '%s'", argv[i]);
			return FALSE;
		} else if (a_i) {
			Log_print("Invalid argument for '%s'", argv[--i]);
			return FALSE;
		}
	}
	*argc = j;

	if (help_only)
		return TRUE;

	/* If filename not given, we must reset the cartridge types. */
	if (CARTRIDGE_main.filename[0] == '\0')
		CARTRIDGE_main.type = CARTRIDGE_NONE;
	if (CARTRIDGE_piggyback.filename[0] == '\0')
		CARTRIDGE_piggyback.type = CARTRIDGE_NONE;

	InitInsert(&CARTRIDGE_main);
	if (CartIsPassthrough(CARTRIDGE_main.type))
		InitInsert(&CARTRIDGE_piggyback);

	return TRUE;
}