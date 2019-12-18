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
struct _Libelf_Data {int /*<<< orphan*/ * d_scn; } ;
typedef  int /*<<< orphan*/  Elf_Scn ;

/* Variables and functions */
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESOURCE ; 
 struct _Libelf_Data* calloc (size_t,int) ; 

struct _Libelf_Data *
_libelf_allocate_data(Elf_Scn *s)
{
	struct _Libelf_Data *d;

	if ((d = calloc((size_t) 1, sizeof(*d))) == NULL) {
		LIBELF_SET_ERROR(RESOURCE, 0);
		return (NULL);
	}

	d->d_scn = s;

	return (d);
}