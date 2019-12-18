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
struct vmcp_session {int /*<<< orphan*/  bufsize; scalar_t__ response; } ;
struct inode {int dummy; } ;
struct file {int /*<<< orphan*/ * private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vmcp_session*) ; 

__attribute__((used)) static int vmcp_release(struct inode *inode, struct file *file)
{
	struct vmcp_session *session;

	session = (struct vmcp_session *)file->private_data;
	file->private_data = NULL;
	free_pages((unsigned long)session->response, get_order(session->bufsize));
	kfree(session);
	return 0;
}