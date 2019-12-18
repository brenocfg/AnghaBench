#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {unsigned int vdev_children; scalar_t__ vdev_ms_count; scalar_t__ vdev_id; TYPE_3__* vdev_mg; struct TYPE_13__** vdev_child; } ;
typedef  TYPE_1__ vdev_t ;
typedef  scalar_t__ uint64_t ;
typedef  char* u_longlong_t ;
struct TYPE_14__ {TYPE_1__* spa_root_vdev; } ;
typedef  TYPE_2__ spa_t ;
struct TYPE_15__ {scalar_t__ mg_fragmentation; int /*<<< orphan*/  mg_histogram; TYPE_4__* mg_class; } ;
typedef  TYPE_3__ metaslab_group_t ;
struct TYPE_16__ {int /*<<< orphan*/  mc_histogram; } ;
typedef  TYPE_4__ metaslab_class_t ;

/* Variables and functions */
 int /*<<< orphan*/  RANGE_TREE_HISTOGRAM_SIZE ; 
 scalar_t__ ZFS_FRAG_INVALID ; 
 int /*<<< orphan*/  dump_histogram (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ metaslab_class_fragmentation (TYPE_4__*) ; 
 int /*<<< orphan*/  metaslab_class_histogram_verify (TYPE_4__*) ; 
 scalar_t__ metaslab_group_fragmentation (TYPE_3__*) ; 
 int /*<<< orphan*/  metaslab_group_histogram_verify (TYPE_3__*) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 char* spa_name (TYPE_2__*) ; 
 TYPE_4__* spa_normal_class (TYPE_2__*) ; 

__attribute__((used)) static void
dump_metaslab_groups(spa_t *spa)
{
	vdev_t *rvd = spa->spa_root_vdev;
	metaslab_class_t *mc = spa_normal_class(spa);
	uint64_t fragmentation;

	metaslab_class_histogram_verify(mc);

	for (unsigned c = 0; c < rvd->vdev_children; c++) {
		vdev_t *tvd = rvd->vdev_child[c];
		metaslab_group_t *mg = tvd->vdev_mg;

		if (mg->mg_class != mc)
			continue;

		metaslab_group_histogram_verify(mg);
		mg->mg_fragmentation = metaslab_group_fragmentation(mg);

		(void) printf("\tvdev %10llu\t\tmetaslabs%5llu\t\t"
		    "fragmentation",
		    (u_longlong_t)tvd->vdev_id,
		    (u_longlong_t)tvd->vdev_ms_count);
		if (mg->mg_fragmentation == ZFS_FRAG_INVALID) {
			(void) printf("%3s\n", "-");
		} else {
			(void) printf("%3llu%%\n",
			    (u_longlong_t)mg->mg_fragmentation);
		}
		dump_histogram(mg->mg_histogram, RANGE_TREE_HISTOGRAM_SIZE, 0);
	}

	(void) printf("\tpool %s\tfragmentation", spa_name(spa));
	fragmentation = metaslab_class_fragmentation(mc);
	if (fragmentation == ZFS_FRAG_INVALID)
		(void) printf("\t%3s\n", "-");
	else
		(void) printf("\t%3llu%%\n", (u_longlong_t)fragmentation);
	dump_histogram(mc->mc_histogram, RANGE_TREE_HISTOGRAM_SIZE, 0);
}