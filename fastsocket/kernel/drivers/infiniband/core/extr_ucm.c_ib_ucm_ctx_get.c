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
struct ib_ucm_file {int dummy; } ;
struct ib_ucm_context {int /*<<< orphan*/  ref; struct ib_ucm_file* file; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 struct ib_ucm_context* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctx_id_mutex ; 
 int /*<<< orphan*/  ctx_id_table ; 
 struct ib_ucm_context* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ib_ucm_context *ib_ucm_ctx_get(struct ib_ucm_file *file, int id)
{
	struct ib_ucm_context *ctx;

	mutex_lock(&ctx_id_mutex);
	ctx = idr_find(&ctx_id_table, id);
	if (!ctx)
		ctx = ERR_PTR(-ENOENT);
	else if (ctx->file != file)
		ctx = ERR_PTR(-EINVAL);
	else
		atomic_inc(&ctx->ref);
	mutex_unlock(&ctx_id_mutex);

	return ctx;
}