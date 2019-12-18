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
typedef  int /*<<< orphan*/  u8 ;
struct ctlr_info {int /*<<< orphan*/  cmpQ; TYPE_2__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * CDB; } ;
struct CommandList {int /*<<< orphan*/  scsi_cmd; TYPE_1__ Request; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct CommandList* hpsa_find_cmd_in_queue (struct ctlr_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct CommandList* hpsa_find_cmd_in_queue_by_tag (struct ctlr_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hpsa_send_abort (struct ctlr_info*,unsigned char*,struct CommandList*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  swizzle_abort_tag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hpsa_send_abort_both_ways(struct ctlr_info *h,
	unsigned char *scsi3addr, struct CommandList *abort)
{
	u8 swizzled_tag[8];
	struct CommandList *c;
	int rc = 0, rc2 = 0;

	/* we do not expect to find the swizzled tag in our queue, but
	 * check anyway just to be sure the assumptions which make this
	 * the case haven't become wrong.
	 */
	memcpy(swizzled_tag, &abort->Request.CDB[4], 8);
	swizzle_abort_tag(swizzled_tag);
	c = hpsa_find_cmd_in_queue_by_tag(h, swizzled_tag, &h->cmpQ);
	if (c != NULL) {
		dev_warn(&h->pdev->dev, "Unexpectedly found byte-swapped tag in completion queue.\n");
		return hpsa_send_abort(h, scsi3addr, abort, 0);
	}
	rc = hpsa_send_abort(h, scsi3addr, abort, 0);

	/* if the command is still in our queue, we can't conclude that it was
	 * aborted (it might have just completed normally) but in any case
	 * we don't need to try to abort it another way.
	 */
	c = hpsa_find_cmd_in_queue(h, abort->scsi_cmd, &h->cmpQ);
	if (c)
		rc2 = hpsa_send_abort(h, scsi3addr, abort, 1);
	return rc && rc2;
}