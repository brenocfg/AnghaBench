#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {TYPE_1__* private_data; } ;
struct TYPE_3__ {int connected; scalar_t__ blocked; int /*<<< orphan*/  release; } ;
struct cuse_conn {TYPE_1__ fc; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cuse_fc_release ; 
 int cuse_send_init (struct cuse_conn*) ; 
 int /*<<< orphan*/  fuse_conn_init (TYPE_1__*) ; 
 int /*<<< orphan*/  fuse_conn_put (TYPE_1__*) ; 
 struct cuse_conn* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cuse_channel_open(struct inode *inode, struct file *file)
{
	struct cuse_conn *cc;
	int rc;

	/* set up cuse_conn */
	cc = kzalloc(sizeof(*cc), GFP_KERNEL);
	if (!cc)
		return -ENOMEM;

	fuse_conn_init(&cc->fc);

	INIT_LIST_HEAD(&cc->list);
	cc->fc.release = cuse_fc_release;

	cc->fc.connected = 1;
	cc->fc.blocked = 0;
	rc = cuse_send_init(cc);
	if (rc) {
		fuse_conn_put(&cc->fc);
		return rc;
	}
	file->private_data = &cc->fc;	/* channel owns base reference to cc */

	return 0;
}