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
struct whcrc {struct uwb_rc* uwb_rc; } ;
struct uwb_rc {int dummy; } ;
struct umc_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct whcrc*) ; 
 struct whcrc* umc_get_drvdata (struct umc_dev*) ; 
 int /*<<< orphan*/  umc_set_drvdata (struct umc_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_rc_put (struct uwb_rc*) ; 
 int /*<<< orphan*/  uwb_rc_rm (struct uwb_rc*) ; 
 int /*<<< orphan*/  whcrc_release_rc_umc (struct whcrc*) ; 

__attribute__((used)) static void whcrc_remove(struct umc_dev *umc_dev)
{
	struct whcrc *whcrc = umc_get_drvdata(umc_dev);
	struct uwb_rc *uwb_rc = whcrc->uwb_rc;

	umc_set_drvdata(umc_dev, NULL);
	uwb_rc_rm(uwb_rc);
	whcrc_release_rc_umc(whcrc);
	kfree(whcrc);
	uwb_rc_put(uwb_rc);
}