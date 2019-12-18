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
struct txdb {scalar_t__ rptr; scalar_t__ wptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDX_ASSERT (int) ; 
 int /*<<< orphan*/  __bdx_tx_db_ptr_next (struct txdb*,scalar_t__*) ; 

__attribute__((used)) static inline void bdx_tx_db_inc_rptr(struct txdb *db)
{
	BDX_ASSERT(db->rptr == db->wptr);	/* can't read from empty db */
	__bdx_tx_db_ptr_next(db, &db->rptr);
}