#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char* uintmax_t ;
struct readelf {int options; char* filename; int /*<<< orphan*/ * ar; int /*<<< orphan*/ * elf; } ;
typedef  scalar_t__ off_t ;
struct TYPE_6__ {char* ar_name; } ;
struct TYPE_5__ {char* as_name; scalar_t__ as_off; } ;
typedef  int /*<<< orphan*/  Elf_Cmd ;
typedef  TYPE_1__ Elf_Arsym ;
typedef  TYPE_2__ Elf_Arhdr ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_C_READ ; 
 int RE_C ; 
 scalar_t__ SARMAG ; 
 int /*<<< orphan*/  dump_elf (struct readelf*) ; 
 void* elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 TYPE_2__* elf_getarhdr (int /*<<< orphan*/ *) ; 
 TYPE_1__* elf_getarsym (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  elf_next (int /*<<< orphan*/ *) ; 
 scalar_t__ elf_rand (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_ar(struct readelf *re, int fd)
{
	Elf_Arsym *arsym;
	Elf_Arhdr *arhdr;
	Elf_Cmd cmd;
	Elf *e;
	size_t sz;
	off_t off;
	int i;

	re->ar = re->elf;

	if (re->options & RE_C) {
		if ((arsym = elf_getarsym(re->ar, &sz)) == NULL) {
			warnx("elf_getarsym() failed: %s", elf_errmsg(-1));
			goto process_members;
		}
		printf("Index of archive %s: (%ju entries)\n", re->filename,
		    (uintmax_t) sz - 1);
		off = 0;
		for (i = 0; (size_t) i < sz; i++) {
			if (arsym[i].as_name == NULL)
				break;
			if (arsym[i].as_off != off) {
				off = arsym[i].as_off;
				if (elf_rand(re->ar, off) != off) {
					warnx("elf_rand() failed: %s",
					    elf_errmsg(-1));
					continue;
				}
				if ((e = elf_begin(fd, ELF_C_READ, re->ar)) ==
				    NULL) {
					warnx("elf_begin() failed: %s",
					    elf_errmsg(-1));
					continue;
				}
				if ((arhdr = elf_getarhdr(e)) == NULL) {
					warnx("elf_getarhdr() failed: %s",
					    elf_errmsg(-1));
					elf_end(e);
					continue;
				}
				printf("Binary %s(%s) contains:\n",
				    re->filename, arhdr->ar_name);
			}
			printf("\t%s\n", arsym[i].as_name);
		}
		if (elf_rand(re->ar, SARMAG) != SARMAG) {
			warnx("elf_rand() failed: %s", elf_errmsg(-1));
			return;
		}
	}

process_members:

	if ((re->options & ~RE_C) == 0)
		return;

	cmd = ELF_C_READ;
	while ((re->elf = elf_begin(fd, cmd, re->ar)) != NULL) {
		if ((arhdr = elf_getarhdr(re->elf)) == NULL) {
			warnx("elf_getarhdr() failed: %s", elf_errmsg(-1));
			goto next_member;
		}
		if (strcmp(arhdr->ar_name, "/") == 0 ||
		    strcmp(arhdr->ar_name, "//") == 0 ||
		    strcmp(arhdr->ar_name, "__.SYMDEF") == 0)
			goto next_member;
		printf("\nFile: %s(%s)\n", re->filename, arhdr->ar_name);
		dump_elf(re);

	next_member:
		cmd = elf_next(re->elf);
		elf_end(re->elf);
	}
	re->elf = re->ar;
}