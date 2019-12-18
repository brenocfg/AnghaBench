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
typedef  scalar_t__ uint32_t ;
struct dm_cell_key {int dummy; } ;
struct dm_bio_prison_cell {int /*<<< orphan*/  list; int /*<<< orphan*/  bios; struct bio* holder; int /*<<< orphan*/  key; } ;
struct dm_bio_prison {scalar_t__ cells; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dm_cell_key*,int) ; 

__attribute__((used)) static void __setup_new_cell(struct dm_bio_prison *prison,
			     struct dm_cell_key *key,
			     struct bio *holder,
			     uint32_t hash,
			     struct dm_bio_prison_cell *cell)
{
	memcpy(&cell->key, key, sizeof(cell->key));
	cell->holder = holder;
	bio_list_init(&cell->bios);
	hlist_add_head(&cell->list, prison->cells + hash);
}