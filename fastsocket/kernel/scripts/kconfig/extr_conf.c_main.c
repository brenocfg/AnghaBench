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
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct stat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  LOCALEDIR ; 
 int /*<<< orphan*/  PACKAGE ; 
 int /*<<< orphan*/  S_DEF_USER ; 
 char* _ (char*) ; 
#define  ask_all 137 
#define  ask_new 136 
#define  ask_silent 135 
 int /*<<< orphan*/  bindtextdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_conf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conf_cnt ; 
 scalar_t__ conf_get_changed () ; 
 char* conf_get_configname () ; 
 char* conf_get_default_confname () ; 
 int /*<<< orphan*/  conf_parse (char const*) ; 
 int /*<<< orphan*/  conf_read (char*) ; 
 int /*<<< orphan*/  conf_read_simple (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conf_set_all_new_symbols (int /*<<< orphan*/ ) ; 
 scalar_t__ conf_write (int /*<<< orphan*/ *) ; 
 scalar_t__ conf_write_autoconf () ; 
 int /*<<< orphan*/  def_default ; 
 int /*<<< orphan*/  def_mod ; 
 int /*<<< orphan*/  def_no ; 
 int /*<<< orphan*/  def_random ; 
 int /*<<< orphan*/  def_yes ; 
 char* defconfig_file ; 
#define  dont_ask 134 
#define  dont_ask_dont_tell 133 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* getenv (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int input_mode ; 
 scalar_t__ isatty (int) ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int return_value ; 
 int /*<<< orphan*/ * rootEntry ; 
 int /*<<< orphan*/  rootmenu ; 
#define  set_default 132 
#define  set_mod 131 
#define  set_no 130 
#define  set_random 129 
#define  set_yes 128 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  srand (unsigned int) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 int sync_kconfig ; 
 int /*<<< orphan*/  textdomain (int /*<<< orphan*/ ) ; 
 int valid_stdin ; 

int main(int ac, char **av)
{
	int opt;
	const char *name;
	struct stat tmpstat;

	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);

 	while ((opt = getopt(ac, av, "osbBdD:nmyrh")) != -1) {
		switch (opt) {
		case 'o':
			input_mode = ask_silent;
			break;
		case 's':
			input_mode = ask_silent;
			sync_kconfig = 1;
			break;
		case 'b':
			input_mode = dont_ask;
			break;
		case 'B':
			input_mode = dont_ask_dont_tell;
			break;
		case 'd':
			input_mode = set_default;
			break;
		case 'D':
			input_mode = set_default;
			defconfig_file = optarg;
			break;
		case 'n':
			input_mode = set_no;
			break;
		case 'm':
			input_mode = set_mod;
			break;
		case 'y':
			input_mode = set_yes;
			break;
		case 'r':
		{
			struct timeval now;
			unsigned int seed;

			/*
			 * Use microseconds derived seed,
			 * compensate for systems where it may be zero
			 */
			gettimeofday(&now, NULL);

			seed = (unsigned int)((now.tv_sec + 1) * (now.tv_usec + 1));
			srand(seed);

			input_mode = set_random;
			break;
		}
		case 'h':
			printf(_("See README for usage info\n"));
			exit(0);
			break;
		default:
			fprintf(stderr, _("See README for usage info\n"));
			exit(1);
		}
	}
	if (ac == optind) {
		printf(_("%s: Kconfig file missing\n"), av[0]);
		exit(1);
	}
	name = av[optind];
	conf_parse(name);
	//zconfdump(stdout);
	if (sync_kconfig) {
		name = conf_get_configname();
		if (stat(name, &tmpstat)) {
			fprintf(stderr, _("***\n"
				"*** You have not yet configured your kernel!\n"
				"*** (missing kernel config file \"%s\")\n"
				"***\n"
				"*** Please run some configurator (e.g. \"make oldconfig\" or\n"
				"*** \"make menuconfig\" or \"make xconfig\").\n"
				"***\n"), name);
			exit(1);
		}
	}

	switch (input_mode) {
	case set_default:
		if (!defconfig_file)
			defconfig_file = conf_get_default_confname();
		if (conf_read(defconfig_file)) {
			printf(_("***\n"
				"*** Can't find default configuration \"%s\"!\n"
				"***\n"), defconfig_file);
			exit(1);
		}
		break;
	case ask_silent:
	case ask_all:
	case ask_new:
	case dont_ask:
	case dont_ask_dont_tell:
		conf_read(NULL);
		break;
	case set_no:
	case set_mod:
	case set_yes:
	case set_random:
		name = getenv("KCONFIG_ALLCONFIG");
		if (name && !stat(name, &tmpstat)) {
			conf_read_simple(name, S_DEF_USER);
			break;
		}
		switch (input_mode) {
		case set_no:	 name = "allno.config"; break;
		case set_mod:	 name = "allmod.config"; break;
		case set_yes:	 name = "allyes.config"; break;
		case set_random: name = "allrandom.config"; break;
		default: break;
		}
		if (!stat(name, &tmpstat))
			conf_read_simple(name, S_DEF_USER);
		else if (!stat("all.config", &tmpstat))
			conf_read_simple("all.config", S_DEF_USER);
		break;
	default:
		break;
	}

	if (sync_kconfig) {
		if (conf_get_changed()) {
			name = getenv("KCONFIG_NOSILENTUPDATE");
			if (name && *name) {
				fprintf(stderr,
					_("\n*** Kernel configuration requires explicit update.\n\n"));
				return 1;
			}
		}
		valid_stdin = isatty(0) && isatty(1) && isatty(2);
	}

	switch (input_mode) {
	case set_no:
		conf_set_all_new_symbols(def_no);
		break;
	case set_yes:
		conf_set_all_new_symbols(def_yes);
		break;
	case set_mod:
		conf_set_all_new_symbols(def_mod);
		break;
	case set_random:
		conf_set_all_new_symbols(def_random);
		break;
	case set_default:
		conf_set_all_new_symbols(def_default);
		break;
	case ask_new:
	case ask_all:
		rootEntry = &rootmenu;
		conf(&rootmenu);
		input_mode = ask_silent;
		/* fall through */
	case dont_ask:
	case dont_ask_dont_tell:
	case ask_silent:
		/* Update until a loop caused no more changes */
		do {
			conf_cnt = 0;
			check_conf(&rootmenu);
		} while (conf_cnt &&
			 (input_mode != dont_ask &&
			  input_mode != dont_ask_dont_tell));
		break;
	}

	if (sync_kconfig) {
		/* silentoldconfig is used during the build so we shall update autoconf.
		 * All other commands are only used to generate a config.
		 */
		if (conf_get_changed() && conf_write(NULL)) {
			fprintf(stderr, _("\n*** Error during writing of the kernel configuration.\n\n"));
			exit(1);
		}
		if (conf_write_autoconf()) {
			fprintf(stderr, _("\n*** Error during update of the kernel configuration.\n\n"));
			return 1;
		}
	} else {
		if (conf_write(NULL)) {
			fprintf(stderr, _("\n*** Error during writing of the kernel configuration.\n\n"));
			exit(1);
		}
	}
	return return_value;
}