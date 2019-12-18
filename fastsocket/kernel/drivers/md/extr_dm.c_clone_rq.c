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
struct request {int dummy; } ;
struct mapped_device {int dummy; } ;
struct dm_rq_target_io {struct request clone; int /*<<< orphan*/  info; scalar_t__ error; struct request* orig; int /*<<< orphan*/ * ti; struct mapped_device* md; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct dm_rq_target_io* alloc_rq_tio (struct mapped_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_rq_tio (struct dm_rq_target_io*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ setup_clone (struct request*,struct request*,struct dm_rq_target_io*) ; 

__attribute__((used)) static struct request *clone_rq(struct request *rq, struct mapped_device *md,
				gfp_t gfp_mask)
{
	struct request *clone;
	struct dm_rq_target_io *tio;

	tio = alloc_rq_tio(md, gfp_mask);
	if (!tio)
		return NULL;

	tio->md = md;
	tio->ti = NULL;
	tio->orig = rq;
	tio->error = 0;
	memset(&tio->info, 0, sizeof(tio->info));

	clone = &tio->clone;
	if (setup_clone(clone, rq, tio)) {
		/* -ENOMEM */
		free_rq_tio(tio);
		return NULL;
	}

	return clone;
}