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
struct rxdb {size_t top; int* stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDX_ASSERT (int) ; 

__attribute__((used)) static inline int bdx_rxdb_alloc_elem(struct rxdb *db)
{
	BDX_ASSERT(db->top <= 0);
	return db->stack[--(db->top)];
}