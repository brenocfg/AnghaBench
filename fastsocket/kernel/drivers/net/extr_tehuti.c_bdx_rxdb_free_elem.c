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
struct rxdb {int nelem; int* stack; int /*<<< orphan*/  top; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDX_ASSERT (int) ; 

__attribute__((used)) static inline void bdx_rxdb_free_elem(struct rxdb *db, int n)
{
	BDX_ASSERT((n >= db->nelem) || (n < 0));
	db->stack[(db->top)++] = n;
}