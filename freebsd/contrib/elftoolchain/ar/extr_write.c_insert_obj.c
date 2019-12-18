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
struct bsdar {int options; int /*<<< orphan*/  v_obj; } ;
struct ar_obj {int dummy; } ;

/* Variables and functions */
 int AR_A ; 
 int AR_B ; 
 int /*<<< orphan*/  TAILQ_INSERT_AFTER (int /*<<< orphan*/ *,struct ar_obj*,struct ar_obj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_BEFORE (struct ar_obj*,struct ar_obj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ar_obj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsdar_errc (struct bsdar*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  objs ; 

__attribute__((used)) static void
insert_obj(struct bsdar *bsdar, struct ar_obj *obj, struct ar_obj *pos)
{
	if (obj == NULL)
		bsdar_errc(bsdar, 0, "try to insert a null obj");

	if (pos == NULL || obj == pos)
		/*
		 * If the object to move happens to be the position
		 * obj, or if there is no position obj, move the
		 * object to the end.
		 */
		goto tail;

	if (bsdar->options & AR_B) {
		TAILQ_INSERT_BEFORE(pos, obj, objs);
		return;
	}
	if (bsdar->options & AR_A) {
		TAILQ_INSERT_AFTER(&bsdar->v_obj, pos, obj, objs);
		return;
	}

tail:
	TAILQ_INSERT_TAIL(&bsdar->v_obj, obj, objs);

}