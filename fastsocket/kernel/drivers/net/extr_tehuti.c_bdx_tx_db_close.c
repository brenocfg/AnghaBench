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
struct txdb {int /*<<< orphan*/ * start; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDX_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bdx_tx_db_close(struct txdb *d)
{
	BDX_ASSERT(d == NULL);

	vfree(d->start);
	d->start = NULL;
}