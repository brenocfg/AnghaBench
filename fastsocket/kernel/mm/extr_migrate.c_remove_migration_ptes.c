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
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  remove_migration_pte ; 
 int /*<<< orphan*/  rmap_walk (struct page*,int /*<<< orphan*/ ,struct page*) ; 

__attribute__((used)) static void remove_migration_ptes(struct page *old, struct page *new)
{
	rmap_walk(new, remove_migration_pte, old);
}