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
struct file {int /*<<< orphan*/  private_data; } ;
struct eventfd_ctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct file*) ; 
 struct eventfd_ctx* eventfd_ctx_get (int /*<<< orphan*/ ) ; 
 struct file* eventfd_fget (int) ; 
 int /*<<< orphan*/  fput (struct file*) ; 

struct eventfd_ctx *eventfd_ctx_fdget(int fd)
{
	struct file *file;
	struct eventfd_ctx *ctx;

	file = eventfd_fget(fd);
	if (IS_ERR(file))
		return (struct eventfd_ctx *) file;
	ctx = eventfd_ctx_get(file->private_data);
	fput(file);

	return ctx;
}