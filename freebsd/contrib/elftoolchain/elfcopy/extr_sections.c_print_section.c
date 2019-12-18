#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct section {scalar_t__ sz; int /*<<< orphan*/  is; int /*<<< orphan*/ * buf; } ;
struct TYPE_6__ {scalar_t__ d_size; int /*<<< orphan*/ * d_buf; } ;
typedef  TYPE_1__ Elf_Data ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 TYPE_1__* elf_getdata (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* elf_rawdata (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_data (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static void
print_section(struct section *s)
{
	Elf_Data	*id;
	int		 elferr;

	if (s->buf != NULL && s->sz > 0) {
		print_data(s->buf, s->sz);
	} else {
		id = NULL;
		while ((id = elf_getdata(s->is, id)) != NULL ||
		    (id = elf_rawdata(s->is, id)) != NULL) {
			(void) elf_errno();
			print_data(id->d_buf, id->d_size);
		}
		elferr = elf_errno();
		if (elferr != 0)
			errx(EXIT_FAILURE, "elf_getdata() failed: %s",
			    elf_errmsg(elferr));
	}
	putchar('\n');
}