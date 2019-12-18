#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct idr_layer {int /*<<< orphan*/  count; scalar_t__* ary; } ;
struct ida_bitmap {int nr_busy; int /*<<< orphan*/  bitmap; } ;
struct TYPE_3__ {scalar_t__ id_free_cnt; int /*<<< orphan*/  lock; } ;
struct ida {TYPE_1__ idr; struct ida_bitmap* free_bitmap; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOSPC ; 
 int IDA_BITMAP_BITS ; 
 int IDR_MASK ; 
 int MAX_ID_BIT ; 
 int MAX_LEVEL ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int _idr_rc_to_errno (int) ; 
 int find_next_zero_bit (int /*<<< orphan*/ ,int,int) ; 
 struct idr_layer* get_from_free_list (TYPE_1__*) ; 
 int idr_get_empty_slot (TYPE_1__*,int,struct idr_layer**) ; 
 int /*<<< orphan*/  idr_layer_cache ; 
 int /*<<< orphan*/  idr_mark_full (struct idr_layer**,int) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct idr_layer*) ; 
 int /*<<< orphan*/  memset (struct ida_bitmap*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcu_assign_pointer (scalar_t__,void*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ida_get_new_above(struct ida *ida, int starting_id, int *p_id)
{
	struct idr_layer *pa[MAX_LEVEL];
	struct ida_bitmap *bitmap;
	unsigned long flags;
	int idr_id = starting_id / IDA_BITMAP_BITS;
	int offset = starting_id % IDA_BITMAP_BITS;
	int t, id;

 restart:
	/* get vacant slot */
	t = idr_get_empty_slot(&ida->idr, idr_id, pa);
	if (t < 0)
		return _idr_rc_to_errno(t);

	if (t * IDA_BITMAP_BITS >= MAX_ID_BIT)
		return -ENOSPC;

	if (t != idr_id)
		offset = 0;
	idr_id = t;

	/* if bitmap isn't there, create a new one */
	bitmap = (void *)pa[0]->ary[idr_id & IDR_MASK];
	if (!bitmap) {
		spin_lock_irqsave(&ida->idr.lock, flags);
		bitmap = ida->free_bitmap;
		ida->free_bitmap = NULL;
		spin_unlock_irqrestore(&ida->idr.lock, flags);

		if (!bitmap)
			return -EAGAIN;

		memset(bitmap, 0, sizeof(struct ida_bitmap));
		rcu_assign_pointer(pa[0]->ary[idr_id & IDR_MASK],
				(void *)bitmap);
		pa[0]->count++;
	}

	/* lookup for empty slot */
	t = find_next_zero_bit(bitmap->bitmap, IDA_BITMAP_BITS, offset);
	if (t == IDA_BITMAP_BITS) {
		/* no empty slot after offset, continue to the next chunk */
		idr_id++;
		offset = 0;
		goto restart;
	}

	id = idr_id * IDA_BITMAP_BITS + t;
	if (id >= MAX_ID_BIT)
		return -ENOSPC;

	__set_bit(t, bitmap->bitmap);
	if (++bitmap->nr_busy == IDA_BITMAP_BITS)
		idr_mark_full(pa, idr_id);

	*p_id = id;

	/* Each leaf node can handle nearly a thousand slots and the
	 * whole idea of ida is to have small memory foot print.
	 * Throw away extra resources one by one after each successful
	 * allocation.
	 */
	if (ida->idr.id_free_cnt || ida->free_bitmap) {
		struct idr_layer *p = get_from_free_list(&ida->idr);
		if (p)
			kmem_cache_free(idr_layer_cache, p);
	}

	return 0;
}