#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  path; int /*<<< orphan*/  version; int /*<<< orphan*/  type; } ;
struct p9_wstat {int /*<<< orphan*/ * extension; int /*<<< orphan*/  n_muid; int /*<<< orphan*/  n_gid; int /*<<< orphan*/  n_uid; int /*<<< orphan*/ * muid; int /*<<< orphan*/ * gid; int /*<<< orphan*/ * uid; int /*<<< orphan*/ * name; int /*<<< orphan*/  length; int /*<<< orphan*/  mtime; int /*<<< orphan*/  atime; int /*<<< orphan*/  mode; TYPE_1__ qid; int /*<<< orphan*/  dev; int /*<<< orphan*/  type; } ;

/* Variables and functions */

__attribute__((used)) static void
v9fs_blank_wstat(struct p9_wstat *wstat)
{
	wstat->type = ~0;
	wstat->dev = ~0;
	wstat->qid.type = ~0;
	wstat->qid.version = ~0;
	*((long long *)&wstat->qid.path) = ~0;
	wstat->mode = ~0;
	wstat->atime = ~0;
	wstat->mtime = ~0;
	wstat->length = ~0;
	wstat->name = NULL;
	wstat->uid = NULL;
	wstat->gid = NULL;
	wstat->muid = NULL;
	wstat->n_uid = ~0;
	wstat->n_gid = ~0;
	wstat->n_muid = ~0;
	wstat->extension = NULL;
}