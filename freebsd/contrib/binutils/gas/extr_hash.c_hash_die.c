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
struct hash_control {int /*<<< orphan*/  memory; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct hash_control*) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
hash_die (struct hash_control *table)
{
  obstack_free (&table->memory, 0);
  free (table);
}