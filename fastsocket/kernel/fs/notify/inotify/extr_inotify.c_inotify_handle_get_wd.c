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
struct inotify_watch {scalar_t__ wd; } ;
struct inotify_handle {scalar_t__ last_wd; int /*<<< orphan*/  idr; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int idr_get_new_above (int /*<<< orphan*/ *,struct inotify_watch*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int inotify_handle_get_wd(struct inotify_handle *ih,
				 struct inotify_watch *watch)
{
	int ret;

	do {
		if (unlikely(!idr_pre_get(&ih->idr, GFP_NOFS)))
			return -ENOSPC;
		ret = idr_get_new_above(&ih->idr, watch, ih->last_wd+1, &watch->wd);
	} while (ret == -EAGAIN);

	if (likely(!ret))
		ih->last_wd = watch->wd;

	return ret;
}