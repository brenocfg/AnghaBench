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
struct memelfnote {int datasz; struct elf_note* data; struct elf_note* name; int /*<<< orphan*/  type; } ;
struct elf_note {int n_namesz; int n_descsz; int /*<<< orphan*/  n_type; } ;
typedef  int /*<<< orphan*/  en ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_WRITE (struct elf_note*,int) ; 
 scalar_t__ roundup (unsigned long,int) ; 
 int strlen (struct elf_note*) ; 

__attribute__((used)) static char *storenote(struct memelfnote *men, char *bufp)
{
	struct elf_note en;

#define DUMP_WRITE(addr,nr) do { memcpy(bufp,addr,nr); bufp += nr; } while(0)

	en.n_namesz = strlen(men->name) + 1;
	en.n_descsz = men->datasz;
	en.n_type = men->type;

	DUMP_WRITE(&en, sizeof(en));
	DUMP_WRITE(men->name, en.n_namesz);

	/* XXX - cast from long long to long to avoid need for libgcc.a */
	bufp = (char*) roundup((unsigned long)bufp,4);
	DUMP_WRITE(men->data, men->datasz);
	bufp = (char*) roundup((unsigned long)bufp,4);

#undef DUMP_WRITE

	return bufp;
}