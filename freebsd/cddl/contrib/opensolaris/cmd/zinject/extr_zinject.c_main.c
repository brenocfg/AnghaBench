#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int zi_freq; int zi_duration; scalar_t__ zi_cmd; int zi_iotype; int zi_error; void* zi_type; int /*<<< orphan*/  zi_func; int /*<<< orphan*/  zi_failfast; int /*<<< orphan*/  zi_nlanes; int /*<<< orphan*/  zi_timer; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ zinject_record_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  scalar_t__ err_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int ECHILD ; 
 int ECKSUM ; 
 int EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  LABEL_TYPE (scalar_t__) ; 
 int MAXNAMELEN ; 
 int /*<<< orphan*/  MOS_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  O_RDWR ; 
 scalar_t__ TYPE_INVAL ; 
 int VDEV_STATE_DEGRADED ; 
 int VDEV_STATE_FAULTED ; 
 int VDEV_STATE_UNKNOWN ; 
 int /*<<< orphan*/  ZFS_DEV ; 
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 void* ZINJECT_DATA_FAULT ; 
 int ZINJECT_FLUSH_ARC ; 
 scalar_t__ ZINJECT_IGNORED_WRITES ; 
 int ZINJECT_NULL ; 
 scalar_t__ ZINJECT_PANIC ; 
 scalar_t__ ZINJECT_UNINITIALIZED ; 
 int ZINJECT_UNLOAD_SPA ; 
 int ZIO_TYPES ; 
 int ZIO_TYPE_CLAIM ; 
 int ZIO_TYPE_FREE ; 
 int ZIO_TYPE_READ ; 
 int ZIO_TYPE_WRITE ; 
 void* atoi (char*) ; 
 int cancel_all_handlers () ; 
 int cancel_handler (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * g_zfs ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  libzfs_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libzfs_init () ; 
 int /*<<< orphan*/  libzfs_print_on_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ name_to_type (char*) ; 
 int /*<<< orphan*/  open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int optopt ; 
 int parse_delay (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int perform_action (char*,TYPE_1__*,int) ; 
 scalar_t__ print_all_handlers () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int register_handler (char*,int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ strtol (char*,char**,int) ; 
 scalar_t__ translate_device (char*,char*,scalar_t__,TYPE_1__*) ; 
 scalar_t__ translate_raw (char*,TYPE_1__*) ; 
 scalar_t__ translate_record (scalar_t__,char*,char*,int,TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  zfs_fd ; 
 scalar_t__ zfs_mount (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_unmount (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
main(int argc, char **argv)
{
	int c;
	char *range = NULL;
	char *cancel = NULL;
	char *end;
	char *raw = NULL;
	char *device = NULL;
	int level = 0;
	int quiet = 0;
	int error = 0;
	int domount = 0;
	int io_type = ZIO_TYPES;
	int action = VDEV_STATE_UNKNOWN;
	err_type_t type = TYPE_INVAL;
	err_type_t label = TYPE_INVAL;
	zinject_record_t record = { 0 };
	char pool[MAXNAMELEN];
	char dataset[MAXNAMELEN];
	zfs_handle_t *zhp;
	int nowrites = 0;
	int dur_txg = 0;
	int dur_secs = 0;
	int ret;
	int flags = 0;

	if ((g_zfs = libzfs_init()) == NULL) {
		(void) fprintf(stderr, "internal error: failed to "
		    "initialize ZFS library\n");
		return (1);
	}

	libzfs_print_on_error(g_zfs, B_TRUE);

	if ((zfs_fd = open(ZFS_DEV, O_RDWR)) < 0) {
		(void) fprintf(stderr, "failed to open ZFS device\n");
		return (1);
	}

	if (argc == 1) {
		/*
		 * No arguments.  Print the available handlers.  If there are no
		 * available handlers, direct the user to '-h' for help
		 * information.
		 */
		if (print_all_handlers() == 0) {
			(void) printf("No handlers registered.\n");
			(void) printf("Run 'zinject -h' for usage "
			    "information.\n");
		}

		return (0);
	}

	while ((c = getopt(argc, argv,
	    ":aA:b:d:D:f:Fg:qhIc:t:T:l:mr:s:e:uL:p:")) != -1) {
		switch (c) {
		case 'a':
			flags |= ZINJECT_FLUSH_ARC;
			break;
		case 'A':
			if (strcasecmp(optarg, "degrade") == 0) {
				action = VDEV_STATE_DEGRADED;
			} else if (strcasecmp(optarg, "fault") == 0) {
				action = VDEV_STATE_FAULTED;
			} else {
				(void) fprintf(stderr, "invalid action '%s': "
				    "must be 'degrade' or 'fault'\n", optarg);
				usage();
				return (1);
			}
			break;
		case 'b':
			raw = optarg;
			break;
		case 'c':
			cancel = optarg;
			break;
		case 'd':
			device = optarg;
			break;
		case 'D':
			ret = parse_delay(optarg, &record.zi_timer,
			    &record.zi_nlanes);
			if (ret != 0) {
				(void) fprintf(stderr, "invalid i/o delay "
				    "value: '%s'\n", optarg);
				usage();
				return (1);
			}
			break;
		case 'e':
			if (strcasecmp(optarg, "io") == 0) {
				error = EIO;
			} else if (strcasecmp(optarg, "checksum") == 0) {
				error = ECKSUM;
			} else if (strcasecmp(optarg, "nxio") == 0) {
				error = ENXIO;
			} else if (strcasecmp(optarg, "dtl") == 0) {
				error = ECHILD;
			} else {
				(void) fprintf(stderr, "invalid error type "
				    "'%s': must be 'io', 'checksum' or "
				    "'nxio'\n", optarg);
				usage();
				return (1);
			}
			break;
		case 'f':
			record.zi_freq = atoi(optarg);
			if (record.zi_freq < 1 || record.zi_freq > 100) {
				(void) fprintf(stderr, "frequency range must "
				    "be in the range (0, 100]\n");
				return (1);
			}
			break;
		case 'F':
			record.zi_failfast = B_TRUE;
			break;
		case 'g':
			dur_txg = 1;
			record.zi_duration = (int)strtol(optarg, &end, 10);
			if (record.zi_duration <= 0 || *end != '\0') {
				(void) fprintf(stderr, "invalid duration '%s': "
				    "must be a positive integer\n", optarg);
				usage();
				return (1);
			}
			/* store duration of txgs as its negative */
			record.zi_duration *= -1;
			break;
		case 'h':
			usage();
			return (0);
		case 'I':
			/* default duration, if one hasn't yet been defined */
			nowrites = 1;
			if (dur_secs == 0 && dur_txg == 0)
				record.zi_duration = 30;
			break;
		case 'l':
			level = (int)strtol(optarg, &end, 10);
			if (*end != '\0') {
				(void) fprintf(stderr, "invalid level '%s': "
				    "must be an integer\n", optarg);
				usage();
				return (1);
			}
			break;
		case 'm':
			domount = 1;
			break;
		case 'p':
			(void) strlcpy(record.zi_func, optarg,
			    sizeof (record.zi_func));
			record.zi_cmd = ZINJECT_PANIC;
			break;
		case 'q':
			quiet = 1;
			break;
		case 'r':
			range = optarg;
			break;
		case 's':
			dur_secs = 1;
			record.zi_duration = (int)strtol(optarg, &end, 10);
			if (record.zi_duration <= 0 || *end != '\0') {
				(void) fprintf(stderr, "invalid duration '%s': "
				    "must be a positive integer\n", optarg);
				usage();
				return (1);
			}
			break;
		case 'T':
			if (strcasecmp(optarg, "read") == 0) {
				io_type = ZIO_TYPE_READ;
			} else if (strcasecmp(optarg, "write") == 0) {
				io_type = ZIO_TYPE_WRITE;
			} else if (strcasecmp(optarg, "free") == 0) {
				io_type = ZIO_TYPE_FREE;
			} else if (strcasecmp(optarg, "claim") == 0) {
				io_type = ZIO_TYPE_CLAIM;
			} else if (strcasecmp(optarg, "all") == 0) {
				io_type = ZIO_TYPES;
			} else {
				(void) fprintf(stderr, "invalid I/O type "
				    "'%s': must be 'read', 'write', 'free', "
				    "'claim' or 'all'\n", optarg);
				usage();
				return (1);
			}
			break;
		case 't':
			if ((type = name_to_type(optarg)) == TYPE_INVAL &&
			    !MOS_TYPE(type)) {
				(void) fprintf(stderr, "invalid type '%s'\n",
				    optarg);
				usage();
				return (1);
			}
			break;
		case 'u':
			flags |= ZINJECT_UNLOAD_SPA;
			break;
		case 'L':
			if ((label = name_to_type(optarg)) == TYPE_INVAL &&
			    !LABEL_TYPE(type)) {
				(void) fprintf(stderr, "invalid label type "
				    "'%s'\n", optarg);
				usage();
				return (1);
			}
			break;
		case ':':
			(void) fprintf(stderr, "option -%c requires an "
			    "operand\n", optopt);
			usage();
			return (1);
		case '?':
			(void) fprintf(stderr, "invalid option '%c'\n",
			    optopt);
			usage();
			return (2);
		}
	}

	argc -= optind;
	argv += optind;

	if (record.zi_duration != 0)
		record.zi_cmd = ZINJECT_IGNORED_WRITES;

	if (cancel != NULL) {
		/*
		 * '-c' is invalid with any other options.
		 */
		if (raw != NULL || range != NULL || type != TYPE_INVAL ||
		    level != 0 || record.zi_cmd != ZINJECT_UNINITIALIZED) {
			(void) fprintf(stderr, "cancel (-c) incompatible with "
			    "any other options\n");
			usage();
			return (2);
		}
		if (argc != 0) {
			(void) fprintf(stderr, "extraneous argument to '-c'\n");
			usage();
			return (2);
		}

		if (strcmp(cancel, "all") == 0) {
			return (cancel_all_handlers());
		} else {
			int id = (int)strtol(cancel, &end, 10);
			if (*end != '\0') {
				(void) fprintf(stderr, "invalid handle id '%s':"
				    " must be an integer or 'all'\n", cancel);
				usage();
				return (1);
			}
			return (cancel_handler(id));
		}
	}

	if (device != NULL) {
		/*
		 * Device (-d) injection uses a completely different mechanism
		 * for doing injection, so handle it separately here.
		 */
		if (raw != NULL || range != NULL || type != TYPE_INVAL ||
		    level != 0 || record.zi_cmd != ZINJECT_UNINITIALIZED) {
			(void) fprintf(stderr, "device (-d) incompatible with "
			    "data error injection\n");
			usage();
			return (2);
		}

		if (argc != 1) {
			(void) fprintf(stderr, "device (-d) injection requires "
			    "a single pool name\n");
			usage();
			return (2);
		}

		(void) strcpy(pool, argv[0]);
		dataset[0] = '\0';

		if (error == ECKSUM) {
			(void) fprintf(stderr, "device error type must be "
			    "'io' or 'nxio'\n");
			return (1);
		}

		record.zi_iotype = io_type;
		if (translate_device(pool, device, label, &record) != 0)
			return (1);
		if (!error)
			error = ENXIO;

		if (action != VDEV_STATE_UNKNOWN)
			return (perform_action(pool, &record, action));

	} else if (raw != NULL) {
		if (range != NULL || type != TYPE_INVAL || level != 0 ||
		    record.zi_cmd != ZINJECT_UNINITIALIZED) {
			(void) fprintf(stderr, "raw (-b) format with "
			    "any other options\n");
			usage();
			return (2);
		}

		if (argc != 1) {
			(void) fprintf(stderr, "raw (-b) format expects a "
			    "single pool name\n");
			usage();
			return (2);
		}

		(void) strcpy(pool, argv[0]);
		dataset[0] = '\0';

		if (error == ENXIO) {
			(void) fprintf(stderr, "data error type must be "
			    "'checksum' or 'io'\n");
			return (1);
		}

		record.zi_cmd = ZINJECT_DATA_FAULT;
		if (translate_raw(raw, &record) != 0)
			return (1);
		if (!error)
			error = EIO;
	} else if (record.zi_cmd == ZINJECT_PANIC) {
		if (raw != NULL || range != NULL || type != TYPE_INVAL ||
		    level != 0 || device != NULL) {
			(void) fprintf(stderr, "panic (-p) incompatible with "
			    "other options\n");
			usage();
			return (2);
		}

		if (argc < 1 || argc > 2) {
			(void) fprintf(stderr, "panic (-p) injection requires "
			    "a single pool name and an optional id\n");
			usage();
			return (2);
		}

		(void) strcpy(pool, argv[0]);
		if (argv[1] != NULL)
			record.zi_type = atoi(argv[1]);
		dataset[0] = '\0';
	} else if (record.zi_cmd == ZINJECT_IGNORED_WRITES) {
		if (nowrites == 0) {
			(void) fprintf(stderr, "-s or -g meaningless "
			    "without -I (ignore writes)\n");
			usage();
			return (2);
		} else if (dur_secs && dur_txg) {
			(void) fprintf(stderr, "choose a duration either "
			    "in seconds (-s) or a number of txgs (-g) "
			    "but not both\n");
			usage();
			return (2);
		} else if (argc != 1) {
			(void) fprintf(stderr, "ignore writes (-I) "
			    "injection requires a single pool name\n");
			usage();
			return (2);
		}

		(void) strcpy(pool, argv[0]);
		dataset[0] = '\0';
	} else if (type == TYPE_INVAL) {
		if (flags == 0) {
			(void) fprintf(stderr, "at least one of '-b', '-d', "
			    "'-t', '-a', '-p', '-I' or '-u' "
			    "must be specified\n");
			usage();
			return (2);
		}

		if (argc == 1 && (flags & ZINJECT_UNLOAD_SPA)) {
			(void) strcpy(pool, argv[0]);
			dataset[0] = '\0';
		} else if (argc != 0) {
			(void) fprintf(stderr, "extraneous argument for "
			    "'-f'\n");
			usage();
			return (2);
		}

		flags |= ZINJECT_NULL;
	} else {
		if (argc != 1) {
			(void) fprintf(stderr, "missing object\n");
			usage();
			return (2);
		}

		if (error == ENXIO) {
			(void) fprintf(stderr, "data error type must be "
			    "'checksum' or 'io'\n");
			return (1);
		}

		record.zi_cmd = ZINJECT_DATA_FAULT;
		if (translate_record(type, argv[0], range, level, &record, pool,
		    dataset) != 0)
			return (1);
		if (!error)
			error = EIO;
	}

	/*
	 * If this is pool-wide metadata, unmount everything.  The ioctl() will
	 * unload the pool, so that we trigger spa-wide reopen of metadata next
	 * time we access the pool.
	 */
	if (dataset[0] != '\0' && domount) {
		if ((zhp = zfs_open(g_zfs, dataset, ZFS_TYPE_DATASET)) == NULL)
			return (1);

		if (zfs_unmount(zhp, NULL, 0) != 0)
			return (1);
	}

	record.zi_error = error;

	ret = register_handler(pool, flags, &record, quiet);

	if (dataset[0] != '\0' && domount)
		ret = (zfs_mount(zhp, NULL, 0) != 0);

	libzfs_fini(g_zfs);

	return (ret);
}