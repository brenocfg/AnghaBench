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
typedef  void* uint64_t ;
struct _Elf_Extent_List {int dummy; } ;
struct _Elf_Extent {int ex_type; void* ex_desc; void* ex_size; void* ex_start; } ;

/* Variables and functions */
 int ELF_EXTENT_EHDR ; 
 int ELF_EXTENT_SHDR ; 
 int /*<<< orphan*/  LAYOUT ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESOURCE ; 
 int /*<<< orphan*/  SLIST_INSERT_AFTER (struct _Elf_Extent*,struct _Elf_Extent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (struct _Elf_Extent_List*,struct _Elf_Extent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _libelf_extent_is_unused (struct _Elf_Extent_List*,void*,void*,struct _Elf_Extent**) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  ex_next ; 
 struct _Elf_Extent* malloc (int) ; 

__attribute__((used)) static int
_libelf_insert_extent(struct _Elf_Extent_List *extents, int type,
    uint64_t start, uint64_t size, void *desc)
{
	struct _Elf_Extent *ex, *prevt;

	assert(type >= ELF_EXTENT_EHDR && type <= ELF_EXTENT_SHDR);

	prevt = NULL;

	/*
	 * If the requested range overlaps with an existing extent,
	 * signal an error.
	 */
	if (!_libelf_extent_is_unused(extents, start, size, &prevt)) {
		LIBELF_SET_ERROR(LAYOUT, 0);
		return (0);
	}

	/* Allocate and fill in a new extent descriptor. */
	if ((ex = malloc(sizeof(struct _Elf_Extent))) == NULL) {
		LIBELF_SET_ERROR(RESOURCE, errno);
		return (0);
	}
	ex->ex_start = start;
	ex->ex_size = size;
	ex->ex_desc = desc;
	ex->ex_type = type;

	/* Insert the region descriptor into the list. */
	if (prevt)
		SLIST_INSERT_AFTER(prevt, ex, ex_next);
	else
		SLIST_INSERT_HEAD(extents, ex, ex_next);
	return (1);
}