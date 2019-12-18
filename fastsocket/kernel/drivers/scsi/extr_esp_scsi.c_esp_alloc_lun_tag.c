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
struct esp_lun_data {int hold; scalar_t__ num_tagged; struct esp_cmd_entry** tagged_cmds; struct esp_cmd_entry* non_tagged_cmd; } ;
struct esp_cmd_entry {size_t* tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct esp_cmd_entry*) ; 
 int EBUSY ; 

__attribute__((used)) static int esp_alloc_lun_tag(struct esp_cmd_entry *ent,
			     struct esp_lun_data *lp)
{
	if (!ent->tag[0]) {
		/* Non-tagged, slot already taken?  */
		if (lp->non_tagged_cmd)
			return -EBUSY;

		if (lp->hold) {
			/* We are being held by active tagged
			 * commands.
			 */
			if (lp->num_tagged)
				return -EBUSY;

			/* Tagged commands completed, we can unplug
			 * the queue and run this untagged command.
			 */
			lp->hold = 0;
		} else if (lp->num_tagged) {
			/* Plug the queue until num_tagged decreases
			 * to zero in esp_free_lun_tag.
			 */
			lp->hold = 1;
			return -EBUSY;
		}

		lp->non_tagged_cmd = ent;
		return 0;
	} else {
		/* Tagged command, see if blocked by a
		 * non-tagged one.
		 */
		if (lp->non_tagged_cmd || lp->hold)
			return -EBUSY;
	}

	BUG_ON(lp->tagged_cmds[ent->tag[1]]);

	lp->tagged_cmds[ent->tag[1]] = ent;
	lp->num_tagged++;

	return 0;
}