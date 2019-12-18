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
struct iscsi_pool {int max; void** pool; int /*<<< orphan*/ * queue; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __kfifo_put (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  iscsi_pool_free (struct iscsi_pool*) ; 
 int /*<<< orphan*/ * kfifo_init (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void**,void**,int) ; 
 int /*<<< orphan*/  memset (struct iscsi_pool*,int /*<<< orphan*/ ,int) ; 

int
iscsi_pool_init(struct iscsi_pool *q, int max, void ***items, int item_size)
{
	int i, num_arrays = 1;

	memset(q, 0, sizeof(*q));

	q->max = max;

	/* If the user passed an items pointer, he wants a copy of
	 * the array. */
	if (items)
		num_arrays++;
	q->pool = kzalloc(num_arrays * max * sizeof(void*), GFP_KERNEL);
	if (q->pool == NULL)
		return -ENOMEM;

	q->queue = kfifo_init((void*)q->pool, max * sizeof(void*),
			      GFP_KERNEL, NULL);
	if (IS_ERR(q->queue)) {
		q->queue = NULL;
		goto enomem;
	}

	for (i = 0; i < max; i++) {
		q->pool[i] = kzalloc(item_size, GFP_KERNEL);
		if (q->pool[i] == NULL) {
			q->max = i;
			goto enomem;
		}
		__kfifo_put(q->queue, (void*)&q->pool[i], sizeof(void*));
	}

	if (items) {
		*items = q->pool + max;
		memcpy(*items, q->pool, max * sizeof(void *));
	}

	return 0;

enomem:
	iscsi_pool_free(q);
	return -ENOMEM;
}