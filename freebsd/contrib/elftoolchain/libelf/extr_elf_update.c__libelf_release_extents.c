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
struct _Elf_Extent_List {int dummy; } ;
struct _Elf_Extent {int dummy; } ;

/* Variables and functions */
 struct _Elf_Extent* SLIST_FIRST (struct _Elf_Extent_List*) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (struct _Elf_Extent_List*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_next ; 
 int /*<<< orphan*/  free (struct _Elf_Extent*) ; 

__attribute__((used)) static void
_libelf_release_extents(struct _Elf_Extent_List *extents)
{
	struct _Elf_Extent *ex;

	while ((ex = SLIST_FIRST(extents)) != NULL) {
		SLIST_REMOVE_HEAD(extents, ex_next);
		free(ex);
	}
}