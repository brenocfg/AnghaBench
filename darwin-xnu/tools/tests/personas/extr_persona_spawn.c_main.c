#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* persona_id; void* persona_gid; } ;
struct persona_args {int flags; void* override_uid; TYPE_1__ kinfo; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  pa ;
struct TYPE_4__ {int verbose; int wait_for_children; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_CHILD_FAIL ; 
 int PA_HAS_GID ; 
 int PA_HAS_GROUPS ; 
 int PA_HAS_ID ; 
 int PA_HAS_UID ; 
 int PA_NONE ; 
 int PA_OVERRIDE ; 
 int PA_SHOULD_VERIFY ; 
 int /*<<< orphan*/  PERSONA_TEST_NAME ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIG_UNBLOCK ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 void* atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  basename (char*) ; 
 int child_main_loop (int,char**) ; 
 int /*<<< orphan*/  err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errc (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 TYPE_2__ g ; 
 int /*<<< orphan*/  g_child_mtx ; 
 scalar_t__ geteuid () ; 
 char getopt (int,char**,char*) ; 
 void* getuid () ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  infov (char*) ; 
 int /*<<< orphan*/  main_sighandler ; 
 int /*<<< orphan*/  memset (struct persona_args*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  optarg ; 
 size_t optind ; 
 int parse_groupspec (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int spawn_child (int,char**,struct persona_args*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage_main (char*,int) ; 
 int /*<<< orphan*/  waitpid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

int main(int argc, char **argv)
{
	char ch;
	int ret;

	pthread_mutex_init(&g_child_mtx, NULL);

	/*
	 * Defaults
	 */
	g.verbose = 0;
	g.wait_for_children = 1;

	if (argc > 1 && strcmp(argv[1], "child") == 0) {
		optind = 2;
		ret = child_main_loop(argc, argv);
		if (ret != 1)
			exit(ret);
		if (strcmp(argv[optind], "spawn") != 0) {
			printf("child exiting (%s).\n", argv[optind]);
			exit(0);
		}
		optind++;

		/*
		 * If we get here, then the child wants us to continue running
		 * to potentially spawn yet another child process. This is
		 * helpful when testing inherited personas and verifying
		 * persona restrictions.
		 */
	}

	if (geteuid() != 0)
		err("%s must be run as root", argv[0] ? basename(argv[0]) : PERSONA_TEST_NAME);

	struct persona_args pa;
	memset(&pa, 0, sizeof(pa));

	pa.flags = PA_NONE;
	pa.kinfo.persona_id = getuid();

	/*
	 * Argument parse for default overrides:
	 */
	while ((ch = getopt(argc, argv, "Vg:G:I:u:vwh")) != -1) {
		switch (ch) {
		case 'V':
			pa.flags |= PA_SHOULD_VERIFY;
			break;
		case 'g':
			pa.kinfo.persona_gid = atoi(optarg);
			pa.flags |= PA_HAS_GID;
			pa.flags |= PA_OVERRIDE;
			break;
		case 'G':
			ret = parse_groupspec(&pa.kinfo, optarg);
			if (ret < 0)
				err("Invalid groupspec: \"%s\"", optarg);
			pa.flags |= PA_HAS_GROUPS;
			pa.flags |= PA_OVERRIDE;
			break;
		case 'I':
			pa.kinfo.persona_id = atoi(optarg);
			if (pa.kinfo.persona_id == 0)
				err("Invalid Persona ID: %s", optarg);
			pa.flags |= PA_HAS_ID;
			break;
		case 'u':
			pa.override_uid = atoi(optarg);
			pa.flags |= PA_HAS_UID;
			pa.flags |= PA_OVERRIDE;
			break;
		case 'v':
			g.verbose = 1;
			break;
		case 'w':
			g.wait_for_children = 0;
			break;
		case 'h':
		case '?':
			usage_main(argv[0], 1);
		case ':':
		default:
			printf("Invalid option: '%c'\n", ch);
			usage_main(argv[0], 0);
		}
	}

	if (pa.flags & PA_SHOULD_VERIFY)
		pa.flags = ~PA_OVERRIDE;

	if (optind >= argc) {
		printf("No program given!\n");
		usage_main(argv[0], 0);
	}

	argc -= optind;
	for (int i = 0; i < argc; i++) {
		argv[i] = argv[i + optind];
	}

	argv[argc] = NULL;

	ret = spawn_child(argc, argv, &pa);
	if (ret < 0)
		return ret;

	pid_t child_pid = (pid_t)ret;
	int status = 0;
	sigset_t sigset;
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGCHLD);
	sigprocmask(SIG_UNBLOCK, &sigset, NULL);
	signal(SIGCHLD, main_sighandler);

	if (g.wait_for_children) {
		infov("Waiting for child...");
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status)) {
			status = WEXITSTATUS(status);
			if (status != 0)
				errc(ERR_CHILD_FAIL,
				     "Child exited with status: %d", status);
		}
	}

	info("Done.");
	return 0;
}