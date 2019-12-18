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
struct v9fs_cookie {int /*<<< orphan*/  inode; int /*<<< orphan*/ * qid; int /*<<< orphan*/ * fscache; } ;

/* Variables and functions */
 int /*<<< orphan*/  inode_init_once (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_once(void *foo)
{
	struct v9fs_cookie *vcookie = (struct v9fs_cookie *) foo;
	vcookie->fscache = NULL;
	vcookie->qid = NULL;
	inode_init_once(&vcookie->inode);
}