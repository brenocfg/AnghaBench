#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct _Libelf_Data* d_buf; } ;
struct _Libelf_Data {int d_flags; TYPE_1__ d_data; } ;

/* Variables and functions */
 int LIBELF_F_DATA_MALLOCED ; 
 int /*<<< orphan*/  free (struct _Libelf_Data*) ; 

struct _Libelf_Data *
_libelf_release_data(struct _Libelf_Data *d)
{

	if (d->d_flags & LIBELF_F_DATA_MALLOCED)
		free(d->d_data.d_buf);

	free(d);

	return (NULL);
}