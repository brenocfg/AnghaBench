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
struct ghes {int /*<<< orphan*/  estatus; int /*<<< orphan*/  generic; } ;

/* Variables and functions */
 int /*<<< orphan*/  ghes_clear_estatus (struct ghes*) ; 
 int /*<<< orphan*/  ghes_do_proc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghes_estatus_cache_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghes_estatus_cached (int /*<<< orphan*/ ) ; 
 scalar_t__ ghes_print_estatus (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ghes_read_estatus (struct ghes*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ghes_proc(struct ghes *ghes)
{
	int rc;

	rc = ghes_read_estatus(ghes, 0);
	if (rc)
		goto out;
	if (!ghes_estatus_cached(ghes->estatus)) {
		if (ghes_print_estatus(NULL, ghes->generic, ghes->estatus))
			ghes_estatus_cache_add(ghes->generic, ghes->estatus);
	}
	ghes_do_proc(ghes->estatus);
out:
	ghes_clear_estatus(ghes);
	return 0;
}