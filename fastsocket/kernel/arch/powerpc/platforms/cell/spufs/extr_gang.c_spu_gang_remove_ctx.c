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
struct spu_gang {int /*<<< orphan*/  mutex; int /*<<< orphan*/  contexts; int /*<<< orphan*/  aff_flags; } ;
struct spu_context {int /*<<< orphan*/  gang_list; int /*<<< orphan*/  aff_list; struct spu_gang* gang; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFF_OFFSETS_SET ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_spu_gang (struct spu_gang*) ; 

void spu_gang_remove_ctx(struct spu_gang *gang, struct spu_context *ctx)
{
	mutex_lock(&gang->mutex);
	WARN_ON(ctx->gang != gang);
	if (!list_empty(&ctx->aff_list)) {
		list_del_init(&ctx->aff_list);
		gang->aff_flags &= ~AFF_OFFSETS_SET;
	}
	list_del_init(&ctx->gang_list);
	gang->contexts--;
	mutex_unlock(&gang->mutex);

	put_spu_gang(gang);
}