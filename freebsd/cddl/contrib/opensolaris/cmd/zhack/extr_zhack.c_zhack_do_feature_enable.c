#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* fi_uname; char* fi_desc; char* fi_guid; scalar_t__ fi_flags; int /*<<< orphan*/  fi_feature; int /*<<< orphan*/ * fi_depends; } ;
typedef  TYPE_1__ zfeature_info_t ;
struct TYPE_9__ {int /*<<< orphan*/  spa_feat_desc_obj; int /*<<< orphan*/ * spa_meta_objset; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  spa_feature_t ;
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  SPA_FEATURE_NONE ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 scalar_t__ ZFEATURE_FLAG_READONLY_COMPAT ; 
 int /*<<< orphan*/  ZFS_SPACE_CHECK_NORMAL ; 
 int /*<<< orphan*/  dsl_sync_task (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char getopt (int,char**,char*) ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  spa_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_name (TYPE_2__*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  usage () ; 
 scalar_t__ zap_contains (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ zfeature_is_supported (char*) ; 
 int /*<<< orphan*/  zfeature_is_valid_guid (char*) ; 
 int /*<<< orphan*/  zhack_feature_enable_sync ; 
 int /*<<< orphan*/  zhack_spa_open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 

__attribute__((used)) static void
zhack_do_feature_enable(int argc, char **argv)
{
	char c;
	char *desc, *target;
	spa_t *spa;
	objset_t *mos;
	zfeature_info_t feature;
	spa_feature_t nodeps[] = { SPA_FEATURE_NONE };

	/*
	 * Features are not added to the pool's label until their refcounts
	 * are incremented, so fi_mos can just be left as false for now.
	 */
	desc = NULL;
	feature.fi_uname = "zhack";
	feature.fi_flags = 0;
	feature.fi_depends = nodeps;
	feature.fi_feature = SPA_FEATURE_NONE;

	optind = 1;
	while ((c = getopt(argc, argv, "rmd:")) != -1) {
		switch (c) {
		case 'r':
			feature.fi_flags |= ZFEATURE_FLAG_READONLY_COMPAT;
			break;
		case 'd':
			desc = strdup(optarg);
			break;
		default:
			usage();
			break;
		}
	}

	if (desc == NULL)
		desc = strdup("zhack injected");
	feature.fi_desc = desc;

	argc -= optind;
	argv += optind;

	if (argc < 2) {
		(void) fprintf(stderr, "error: missing feature or pool name\n");
		usage();
	}
	target = argv[0];
	feature.fi_guid = argv[1];

	if (!zfeature_is_valid_guid(feature.fi_guid))
		fatal(NULL, FTAG, "invalid feature guid: %s", feature.fi_guid);

	zhack_spa_open(target, B_FALSE, FTAG, &spa);
	mos = spa->spa_meta_objset;

	if (zfeature_is_supported(feature.fi_guid))
		fatal(spa, FTAG, "'%s' is a real feature, will not enable");
	if (0 == zap_contains(mos, spa->spa_feat_desc_obj, feature.fi_guid))
		fatal(spa, FTAG, "feature already enabled: %s",
		    feature.fi_guid);

	VERIFY0(dsl_sync_task(spa_name(spa), NULL,
	    zhack_feature_enable_sync, &feature, 5, ZFS_SPACE_CHECK_NORMAL));

	spa_close(spa, FTAG);

	free(desc);
}