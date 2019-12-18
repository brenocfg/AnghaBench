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
struct pool {int /*<<< orphan*/  prison; } ;
struct dm_bio_prison_cell {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_bio_prison_free_cell (int /*<<< orphan*/ ,struct dm_bio_prison_cell*) ; 
 int /*<<< orphan*/  dm_cell_error (int /*<<< orphan*/ ,struct dm_bio_prison_cell*) ; 

__attribute__((used)) static void cell_error(struct pool *pool,
		       struct dm_bio_prison_cell *cell)
{
	dm_cell_error(pool->prison, cell);
	dm_bio_prison_free_cell(pool->prison, cell);
}