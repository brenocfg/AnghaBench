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
struct tdef {int dummy; } ;

/* Variables and functions */
 struct tdef* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct tdef*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  tdefs ; 

__attribute__((used)) static void
tdefs_cleanup(void)
{
	struct tdef *t;

	while ((t = SLIST_FIRST(&tdefs)) != NULL) {
		SLIST_REMOVE_HEAD(&tdefs, link);
		free(t);
	}
}