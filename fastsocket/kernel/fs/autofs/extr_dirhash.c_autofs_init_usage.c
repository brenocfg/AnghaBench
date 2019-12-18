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
struct autofs_dirhash {int /*<<< orphan*/  expiry_head; } ;
struct autofs_dir_ent {int /*<<< orphan*/  last_usage; int /*<<< orphan*/  exp; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void autofs_init_usage(struct autofs_dirhash *dh,
			      struct autofs_dir_ent *ent)
{
	list_add_tail(&ent->exp, &dh->expiry_head);
	ent->last_usage = jiffies;
}