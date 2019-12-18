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
struct mousedev_client {scalar_t__ buffer; scalar_t__ ready; struct mousedev* mousedev; } ;
struct mousedev {scalar_t__ exist; int /*<<< orphan*/  wait; } ;
struct file {struct mousedev_client* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 unsigned int POLLERR ; 
 unsigned int POLLHUP ; 
 unsigned int POLLIN ; 
 unsigned int POLLRDNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int mousedev_poll(struct file *file, poll_table *wait)
{
	struct mousedev_client *client = file->private_data;
	struct mousedev *mousedev = client->mousedev;

	poll_wait(file, &mousedev->wait, wait);
	return ((client->ready || client->buffer) ? (POLLIN | POLLRDNORM) : 0) |
		(mousedev->exist ? 0 : (POLLHUP | POLLERR));
}