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
struct ocfs2_super {struct ocfs2_replay_map* replay_map; } ;
struct ocfs2_replay_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ocfs2_replay_map*) ; 

void ocfs2_free_replay_slots(struct ocfs2_super *osb)
{
	struct ocfs2_replay_map *replay_map = osb->replay_map;

	if (!osb->replay_map)
		return;

	kfree(replay_map);
	osb->replay_map = NULL;
}