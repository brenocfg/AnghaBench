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
struct channel_path {int /*<<< orphan*/  desc_fmt1; int /*<<< orphan*/  chpid; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int chsc_determine_base_channel_path_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int chsc_determine_fmt1_channel_path_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int chp_update_desc(struct channel_path *chp)
{
	int rc;

	rc = chsc_determine_base_channel_path_desc(chp->chpid, &chp->desc);
	if (rc)
		return rc;

	rc = chsc_determine_fmt1_channel_path_desc(chp->chpid, &chp->desc_fmt1);

	return rc;
}