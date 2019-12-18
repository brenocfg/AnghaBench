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
struct vmcp_session {int /*<<< orphan*/  mutex; scalar_t__ resp_size; int /*<<< orphan*/ * response; int /*<<< orphan*/  bufsize; } ;
struct inode {int dummy; } ;
struct file {struct vmcp_session* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct vmcp_session* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int nonseekable_open (struct inode*,struct file*) ; 

__attribute__((used)) static int vmcp_open(struct inode *inode, struct file *file)
{
	struct vmcp_session *session;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	session = kmalloc(sizeof(*session), GFP_KERNEL);
	if (!session)
		return -ENOMEM;

	session->bufsize = PAGE_SIZE;
	session->response = NULL;
	session->resp_size = 0;
	mutex_init(&session->mutex);
	file->private_data = session;
	return nonseekable_open(inode, file);
}