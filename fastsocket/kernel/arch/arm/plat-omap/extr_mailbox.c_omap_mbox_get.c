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
struct omap_mbox {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOENT ; 
 struct omap_mbox* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct omap_mbox** find_mboxes (char const*) ; 
 int /*<<< orphan*/  mboxes_lock ; 
 int omap_mbox_init (struct omap_mbox*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

struct omap_mbox *omap_mbox_get(const char *name)
{
	struct omap_mbox *mbox;
	int ret;

	read_lock(&mboxes_lock);
	mbox = *(find_mboxes(name));
	if (mbox == NULL) {
		read_unlock(&mboxes_lock);
		return ERR_PTR(-ENOENT);
	}

	read_unlock(&mboxes_lock);

	ret = omap_mbox_init(mbox);
	if (ret)
		return ERR_PTR(-ENODEV);

	return mbox;
}