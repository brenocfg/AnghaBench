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
typedef  void* u32 ;
struct cnic_id_tbl {int /*<<< orphan*/  table; int /*<<< orphan*/  lock; void* next; void* max; void* start; } ;

/* Variables and functions */
 int DIV_ROUND_UP (void*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cnic_init_id_tbl(struct cnic_id_tbl *id_tbl, u32 size, u32 start_id,
			    u32 next)
{
	id_tbl->start = start_id;
	id_tbl->max = size;
	id_tbl->next = next;
	spin_lock_init(&id_tbl->lock);
	id_tbl->table = kzalloc(DIV_ROUND_UP(size, 32) * 4, GFP_KERNEL);
	if (!id_tbl->table)
		return -ENOMEM;

	return 0;
}