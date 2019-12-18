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
struct file {int dummy; } ;
struct eventfd_ctx {unsigned int count; int flags; int /*<<< orphan*/  wqh; int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ EFD_CLOEXEC ; 
 int EFD_FLAGS_SET ; 
 scalar_t__ EFD_NONBLOCK ; 
 int EFD_SHARED_FCNTL_FLAGS ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct file* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct file*) ; 
 scalar_t__ O_CLOEXEC ; 
 scalar_t__ O_NONBLOCK ; 
 struct file* anon_inode_getfile (char*,int /*<<< orphan*/ *,struct eventfd_ctx*,int) ; 
 int /*<<< orphan*/  eventfd_fops ; 
 int /*<<< orphan*/  eventfd_free_ctx (struct eventfd_ctx*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct eventfd_ctx* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 

struct file *eventfd_file_create(unsigned int count, int flags)
{
	struct file *file;
	struct eventfd_ctx *ctx;

	/* Check the EFD_* constants for consistency.  */
	BUILD_BUG_ON(EFD_CLOEXEC != O_CLOEXEC);
	BUILD_BUG_ON(EFD_NONBLOCK != O_NONBLOCK);

	if (flags & ~EFD_FLAGS_SET)
		return ERR_PTR(-EINVAL);

	ctx = kmalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return ERR_PTR(-ENOMEM);

	kref_init(&ctx->kref);
	init_waitqueue_head(&ctx->wqh);
	ctx->count = count;
	ctx->flags = flags;

	file = anon_inode_getfile("[eventfd]", &eventfd_fops, ctx,
				  flags & EFD_SHARED_FCNTL_FLAGS);
	if (IS_ERR(file))
		eventfd_free_ctx(ctx);

	return file;
}