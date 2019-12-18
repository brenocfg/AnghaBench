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
struct ocfs2_super {int max_slots; int /*<<< orphan*/  osb_lock; struct ocfs2_replay_map* replay_map; } ;
struct ocfs2_replay_map {int rm_slots; int* rm_replay_slots; int /*<<< orphan*/  rm_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  REPLAY_UNNEEDED ; 
 struct ocfs2_replay_map* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_slot_to_node_num_locked (struct ocfs2_super*,int,int*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ocfs2_compute_replay_slots(struct ocfs2_super *osb)
{
	struct ocfs2_replay_map *replay_map;
	int i, node_num;

	/* If replay map is already set, we don't do it again */
	if (osb->replay_map)
		return 0;

	replay_map = kzalloc(sizeof(struct ocfs2_replay_map) +
			     (osb->max_slots * sizeof(char)), GFP_KERNEL);

	if (!replay_map) {
		mlog_errno(-ENOMEM);
		return -ENOMEM;
	}

	spin_lock(&osb->osb_lock);

	replay_map->rm_slots = osb->max_slots;
	replay_map->rm_state = REPLAY_UNNEEDED;

	/* set rm_replay_slots for offline slot(s) */
	for (i = 0; i < replay_map->rm_slots; i++) {
		if (ocfs2_slot_to_node_num_locked(osb, i, &node_num) == -ENOENT)
			replay_map->rm_replay_slots[i] = 1;
	}

	osb->replay_map = replay_map;
	spin_unlock(&osb->osb_lock);
	return 0;
}