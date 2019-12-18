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
struct file {int /*<<< orphan*/  private_data; int /*<<< orphan*/ * f_op; } ;
struct eventfd_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct eventfd_ctx* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct eventfd_ctx* eventfd_ctx_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eventfd_fops ; 

struct eventfd_ctx *eventfd_ctx_fileget(struct file *file)
{
	if (file->f_op != &eventfd_fops)
		return ERR_PTR(-EINVAL);

	return eventfd_ctx_get(file->private_data);
}