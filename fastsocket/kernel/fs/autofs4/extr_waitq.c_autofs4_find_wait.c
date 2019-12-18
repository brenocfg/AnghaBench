#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qstr {scalar_t__ hash; scalar_t__ len; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {scalar_t__ hash; scalar_t__ len; scalar_t__ name; } ;
struct autofs_wait_queue {TYPE_1__ name; struct autofs_wait_queue* next; } ;
struct autofs_sb_info {struct autofs_wait_queue* queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static struct autofs_wait_queue *
autofs4_find_wait(struct autofs_sb_info *sbi, struct qstr *qstr)
{
	struct autofs_wait_queue *wq;

	for (wq = sbi->queues; wq; wq = wq->next) {
		if (wq->name.hash == qstr->hash &&
		    wq->name.len == qstr->len &&
		    wq->name.name &&
			 !memcmp(wq->name.name, qstr->name, qstr->len))
			break;
	}
	return wq;
}