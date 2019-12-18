#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
struct rlimit {int member_0; int member_1; } ;
struct TYPE_8__ {scalar_t__ spa_log_state; int /*<<< orphan*/ * spa_meta_objset; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  void* boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 void* B_FALSE ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  DMU_OST_ANY ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FREAD ; 
 int /*<<< orphan*/  FTAG ; 
 int MAX (int,int) ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME_TYPE ; 
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 scalar_t__ SPA_LOG_CLEAR ; 
 scalar_t__ SPA_LOG_MISSING ; 
 void* TXG_INITIAL ; 
 void* UINT64_MAX ; 
 int /*<<< orphan*/  UMEM_NOFAIL ; 
 int /*<<< orphan*/  ZDB_FLAG_BSWAP ; 
 int /*<<< orphan*/  ZDB_FLAG_CHECKSUM ; 
 int /*<<< orphan*/  ZDB_FLAG_DECOMPRESS ; 
 int /*<<< orphan*/  ZDB_FLAG_GBH ; 
 int /*<<< orphan*/  ZDB_FLAG_INDIRECT ; 
 int /*<<< orphan*/  ZDB_FLAG_PHYS ; 
 int /*<<< orphan*/  ZDB_FLAG_PRINT_BLKPTR ; 
 int /*<<< orphan*/  ZDB_FLAG_RAW ; 
 int ZFS_IMPORT_MISSING_LOG ; 
 int ZFS_IMPORT_VERBATIM ; 
 int ZPOOL_DO_REWIND ; 
 int ZPOOL_EXTREME_REWIND ; 
 int /*<<< orphan*/  ZPOOL_LOAD_POLICY ; 
 int /*<<< orphan*/  ZPOOL_LOAD_REQUEST_TXG ; 
 int /*<<< orphan*/  ZPOOL_LOAD_REWIND_POLICY ; 
 int ZPOOL_NEVER_REWIND ; 
 int aok ; 
 int /*<<< orphan*/  bcopy (char**,char**,int) ; 
 scalar_t__* calloc (unsigned int,int) ; 
 int /*<<< orphan*/  close_objset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf_setup (int*,char**) ; 
 int /*<<< orphan*/  dump_cachefile (char*) ; 
 int /*<<< orphan*/  dump_debug_buffer () ; 
 int /*<<< orphan*/  dump_dir (int /*<<< orphan*/ *) ; 
 int dump_label (char*) ; 
 int /*<<< orphan*/  dump_nvlist (int /*<<< orphan*/ *,int) ; 
 int* dump_opt ; 
 int dump_path (char*,char*) ; 
 int /*<<< orphan*/  dump_zpool (TYPE_1__*) ; 
 int /*<<< orphan*/  enable_extended_FILE_stdio (int,int) ; 
 int errno ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 char* find_zpool (char**,int /*<<< orphan*/ **,int,char**) ; 
 int /*<<< orphan*/ * flagbits ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fuid_table_destroy () ; 
 int /*<<< orphan*/ * g_zfs ; 
 char* getenv (char*) ; 
 int getopt (int,char**,char*) ; 
 char* import_checkpointed_state (char*,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  kernel_fini () ; 
 int /*<<< orphan*/  kernel_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libzfs_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libzfs_init () ; 
 void* max_inflight ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_add_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_add_uint32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int open_objset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*) ; 
 void* reference_tracking_enable ; 
 int set_global_var (char*) ; 
 int /*<<< orphan*/  setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  spa_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* spa_config_path ; 
 int spa_import (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* spa_load_verify_dryrun ; 
 TYPE_1__* spa_lookup (char*) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int spa_open (char*,TYPE_1__**,int /*<<< orphan*/ ) ; 
 int spa_open_rewind (char*,TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * strchr (char*,int) ; 
 int strerror (int) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/ * strpbrk (char*,char*) ; 
 void* strtoull (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char** umem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umem_free (char**,int) ; 
 int /*<<< orphan*/  usage () ; 
 char* vn_dumpdir ; 
 int /*<<< orphan*/  zdb_embedded_block (char*) ; 
 int /*<<< orphan*/  zdb_read_block (char*,TYPE_1__*) ; 
 int zfs_arc_max ; 
 int zfs_arc_meta_limit ; 
 int zfs_recover ; 
 int zfs_vdev_async_read_max_active ; 
 scalar_t__* zopt_object ; 
 unsigned int zopt_objects ; 

int
main(int argc, char **argv)
{
	int c;
	struct rlimit rl = { 1024, 1024 };
	spa_t *spa = NULL;
	objset_t *os = NULL;
	int dump_all = 1;
	int verbose = 0;
	int error = 0;
	char **searchdirs = NULL;
	int nsearch = 0;
	char *target;
	nvlist_t *policy = NULL;
	uint64_t max_txg = UINT64_MAX;
	int flags = ZFS_IMPORT_MISSING_LOG;
	int rewind = ZPOOL_NEVER_REWIND;
	char *spa_config_path_env;
	boolean_t target_is_spa = B_TRUE;
	nvlist_t *cfg = NULL;

	(void) setrlimit(RLIMIT_NOFILE, &rl);
	(void) enable_extended_FILE_stdio(-1, -1);

	dprintf_setup(&argc, argv);

	/*
	 * If there is an environment variable SPA_CONFIG_PATH it overrides
	 * default spa_config_path setting. If -U flag is specified it will
	 * override this environment variable settings once again.
	 */
	spa_config_path_env = getenv("SPA_CONFIG_PATH");
	if (spa_config_path_env != NULL)
		spa_config_path = spa_config_path_env;

	while ((c = getopt(argc, argv,
	    "AbcCdDeEFGhiI:klLmMo:Op:PqRsSt:uU:vVx:X")) != -1) {
		switch (c) {
		case 'b':
		case 'c':
		case 'C':
		case 'd':
		case 'D':
		case 'E':
		case 'G':
		case 'h':
		case 'i':
		case 'l':
		case 'm':
		case 'M':
		case 'O':
		case 'R':
		case 's':
		case 'S':
		case 'u':
			dump_opt[c]++;
			dump_all = 0;
			break;
		case 'A':
		case 'e':
		case 'F':
		case 'k':
		case 'L':
		case 'P':
		case 'q':
		case 'X':
			dump_opt[c]++;
			break;
		/* NB: Sort single match options below. */
		case 'I':
			max_inflight = strtoull(optarg, NULL, 0);
			if (max_inflight == 0) {
				(void) fprintf(stderr, "maximum number "
				    "of inflight I/Os must be greater "
				    "than 0\n");
				usage();
			}
			break;
		case 'o':
			error = set_global_var(optarg);
			if (error != 0)
				usage();
			break;
		case 'p':
			if (searchdirs == NULL) {
				searchdirs = umem_alloc(sizeof (char *),
				    UMEM_NOFAIL);
			} else {
				char **tmp = umem_alloc((nsearch + 1) *
				    sizeof (char *), UMEM_NOFAIL);
				bcopy(searchdirs, tmp, nsearch *
				    sizeof (char *));
				umem_free(searchdirs,
				    nsearch * sizeof (char *));
				searchdirs = tmp;
			}
			searchdirs[nsearch++] = optarg;
			break;
		case 't':
			max_txg = strtoull(optarg, NULL, 0);
			if (max_txg < TXG_INITIAL) {
				(void) fprintf(stderr, "incorrect txg "
				    "specified: %s\n", optarg);
				usage();
			}
			break;
		case 'U':
			spa_config_path = optarg;
			if (spa_config_path[0] != '/') {
				(void) fprintf(stderr,
				    "cachefile must be an absolute path "
				    "(i.e. start with a slash)\n");
				usage();
			}
			break;
		case 'v':
			verbose++;
			break;
		case 'V':
			flags = ZFS_IMPORT_VERBATIM;
			break;
		case 'x':
			vn_dumpdir = optarg;
			break;
		default:
			usage();
			break;
		}
	}

	if (!dump_opt['e'] && searchdirs != NULL) {
		(void) fprintf(stderr, "-p option requires use of -e\n");
		usage();
	}

	/*
	 * ZDB does not typically re-read blocks; therefore limit the ARC
	 * to 256 MB, which can be used entirely for metadata.
	 */
	zfs_arc_max = zfs_arc_meta_limit = 256 * 1024 * 1024;

	/*
	 * "zdb -c" uses checksum-verifying scrub i/os which are async reads.
	 * "zdb -b" uses traversal prefetch which uses async reads.
	 * For good performance, let several of them be active at once.
	 */
	zfs_vdev_async_read_max_active = 10;

	/*
	 * Disable reference tracking for better performance.
	 */
	reference_tracking_enable = B_FALSE;

	/*
	 * Do not fail spa_load when spa_load_verify fails. This is needed
	 * to load non-idle pools.
	 */
	spa_load_verify_dryrun = B_TRUE;

	kernel_init(FREAD);
	g_zfs = libzfs_init();
	if (g_zfs == NULL)
		fatal("Fail to initialize zfs");

	if (dump_all)
		verbose = MAX(verbose, 1);

	for (c = 0; c < 256; c++) {
		if (dump_all && strchr("AeEFklLOPRSX", c) == NULL)
			dump_opt[c] = 1;
		if (dump_opt[c])
			dump_opt[c] += verbose;
	}

	aok = (dump_opt['A'] == 1) || (dump_opt['A'] > 2);
	zfs_recover = (dump_opt['A'] > 1);

	argc -= optind;
	argv += optind;

	if (argc < 2 && dump_opt['R'])
		usage();

	if (dump_opt['E']) {
		if (argc != 1)
			usage();
		zdb_embedded_block(argv[0]);
		return (0);
	}

	if (argc < 1) {
		if (!dump_opt['e'] && dump_opt['C']) {
			dump_cachefile(spa_config_path);
			return (0);
		}
		usage();
	}

	if (dump_opt['l'])
		return (dump_label(argv[0]));

	if (dump_opt['O']) {
		if (argc != 2)
			usage();
		dump_opt['v'] = verbose + 3;
		return (dump_path(argv[0], argv[1]));
	}

	if (dump_opt['X'] || dump_opt['F'])
		rewind = ZPOOL_DO_REWIND |
		    (dump_opt['X'] ? ZPOOL_EXTREME_REWIND : 0);

	if (nvlist_alloc(&policy, NV_UNIQUE_NAME_TYPE, 0) != 0 ||
	    nvlist_add_uint64(policy, ZPOOL_LOAD_REQUEST_TXG, max_txg) != 0 ||
	    nvlist_add_uint32(policy, ZPOOL_LOAD_REWIND_POLICY, rewind) != 0)
		fatal("internal error: %s", strerror(ENOMEM));

	error = 0;
	target = argv[0];

	if (dump_opt['e']) {
		char *name = find_zpool(&target, &cfg, nsearch, searchdirs);

		error = ENOENT;
		if (name) {
			if (dump_opt['C'] > 1) {
				(void) printf("\nConfiguration for import:\n");
				dump_nvlist(cfg, 8);
			}

			if (nvlist_add_nvlist(cfg,
			    ZPOOL_LOAD_POLICY, policy) != 0) {
				fatal("can't open '%s': %s",
				    target, strerror(ENOMEM));
			}
			error = spa_import(name, cfg, NULL, flags);
		}
	}

	char *checkpoint_pool = NULL;
	char *checkpoint_target = NULL;
	if (dump_opt['k']) {
		checkpoint_pool = import_checkpointed_state(target, cfg,
		    &checkpoint_target);

		if (checkpoint_target != NULL)
			target = checkpoint_target;

	}

	if (strpbrk(target, "/@") != NULL) {
		size_t targetlen;

		target_is_spa = B_FALSE;
		/*
		 * Remove any trailing slash.  Later code would get confused
		 * by it, but we want to allow it so that "pool/" can
		 * indicate that we want to dump the topmost filesystem,
		 * rather than the whole pool.
		 */
		targetlen = strlen(target);
		if (targetlen != 0 && target[targetlen - 1] == '/')
			target[targetlen - 1] = '\0';
	}

	if (error == 0) {
		if (dump_opt['k'] && (target_is_spa || dump_opt['R'])) {
			ASSERT(checkpoint_pool != NULL);
			ASSERT(checkpoint_target == NULL);

			error = spa_open(checkpoint_pool, &spa, FTAG);
			if (error != 0) {
				fatal("Tried to open pool \"%s\" but "
				    "spa_open() failed with error %d\n",
				    checkpoint_pool, error);
			}

		} else if (target_is_spa || dump_opt['R']) {
			error = spa_open_rewind(target, &spa, FTAG, policy,
			    NULL);
			if (error) {
				/*
				 * If we're missing the log device then
				 * try opening the pool after clearing the
				 * log state.
				 */
				mutex_enter(&spa_namespace_lock);
				if ((spa = spa_lookup(target)) != NULL &&
				    spa->spa_log_state == SPA_LOG_MISSING) {
					spa->spa_log_state = SPA_LOG_CLEAR;
					error = 0;
				}
				mutex_exit(&spa_namespace_lock);

				if (!error) {
					error = spa_open_rewind(target, &spa,
					    FTAG, policy, NULL);
				}
			}
		} else {
			error = open_objset(target, DMU_OST_ANY, FTAG, &os);
		}
	}
	nvlist_free(policy);

	if (error)
		fatal("can't open '%s': %s", target, strerror(error));

	argv++;
	argc--;
	if (!dump_opt['R']) {
		if (argc > 0) {
			zopt_objects = argc;
			zopt_object = calloc(zopt_objects, sizeof (uint64_t));
			for (unsigned i = 0; i < zopt_objects; i++) {
				errno = 0;
				zopt_object[i] = strtoull(argv[i], NULL, 0);
				if (zopt_object[i] == 0 && errno != 0)
					fatal("bad number %s: %s",
					    argv[i], strerror(errno));
			}
		}
		if (os != NULL) {
			dump_dir(os);
		} else if (zopt_objects > 0 && !dump_opt['m']) {
			dump_dir(spa->spa_meta_objset);
		} else {
			dump_zpool(spa);
		}
	} else {
		flagbits['b'] = ZDB_FLAG_PRINT_BLKPTR;
		flagbits['c'] = ZDB_FLAG_CHECKSUM;
		flagbits['d'] = ZDB_FLAG_DECOMPRESS;
		flagbits['e'] = ZDB_FLAG_BSWAP;
		flagbits['g'] = ZDB_FLAG_GBH;
		flagbits['i'] = ZDB_FLAG_INDIRECT;
		flagbits['p'] = ZDB_FLAG_PHYS;
		flagbits['r'] = ZDB_FLAG_RAW;

		for (int i = 0; i < argc; i++)
			zdb_read_block(argv[i], spa);
	}

	if (dump_opt['k']) {
		free(checkpoint_pool);
		if (!target_is_spa)
			free(checkpoint_target);
	}

	if (os != NULL)
		close_objset(os, FTAG);
	else
		spa_close(spa, FTAG);

	fuid_table_destroy();

	dump_debug_buffer();

	libzfs_fini(g_zfs);
	kernel_fini();

	return (error);
}