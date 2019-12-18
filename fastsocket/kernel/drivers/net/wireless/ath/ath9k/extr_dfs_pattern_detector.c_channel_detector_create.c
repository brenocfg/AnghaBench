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
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct radar_detector_specs {int dummy; } ;
struct pri_detector {int dummy; } ;
struct dfs_pattern_detector {int num_radar_types; int /*<<< orphan*/  channel_detectors; struct radar_detector_specs* radar_spec; int /*<<< orphan*/  ah; } ;
struct channel_detector {int /*<<< orphan*/  head; struct pri_detector** detectors; int /*<<< orphan*/  freq; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  channel_detector_exit (struct dfs_pattern_detector*,struct channel_detector*) ; 
 struct channel_detector* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct pri_detector** kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct pri_detector* pri_detector_init (struct radar_detector_specs const*) ; 

__attribute__((used)) static struct channel_detector *
channel_detector_create(struct dfs_pattern_detector *dpd, u16 freq)
{
	u32 sz, i;
	struct channel_detector *cd;
	struct ath_common *common = ath9k_hw_common(dpd->ah);

	cd = kmalloc(sizeof(*cd), GFP_ATOMIC);
	if (cd == NULL)
		goto fail;

	INIT_LIST_HEAD(&cd->head);
	cd->freq = freq;
	sz = sizeof(cd->detectors) * dpd->num_radar_types;
	cd->detectors = kzalloc(sz, GFP_ATOMIC);
	if (cd->detectors == NULL)
		goto fail;

	for (i = 0; i < dpd->num_radar_types; i++) {
		const struct radar_detector_specs *rs = &dpd->radar_spec[i];
		struct pri_detector *de = pri_detector_init(rs);
		if (de == NULL)
			goto fail;
		cd->detectors[i] = de;
	}
	list_add(&cd->head, &dpd->channel_detectors);
	return cd;

fail:
	ath_dbg(common, DFS,
		"failed to allocate channel_detector for freq=%d\n", freq);
	channel_detector_exit(dpd, cd);
	return NULL;
}