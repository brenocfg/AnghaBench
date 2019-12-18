#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  read_cb_f ;
struct TYPE_3__ {char* ar_name; } ;
typedef  int /*<<< orphan*/  Elf_Cmd ;
typedef  TYPE_1__ Elf_Arhdr ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_C_READ ; 
#define  ELF_K_AR 129 
#define  ELF_K_ELF 128 
 int /*<<< orphan*/ * elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ *) ; 
 TYPE_1__* elf_getarhdr (int /*<<< orphan*/ *) ; 
 int elf_kind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elfterminate (char*,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int read_file (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  terminate (char*,char*,int) ; 
 char* xmalloc (size_t) ; 

__attribute__((used)) static int
read_archive(int fd, Elf *elf, char *file, char *label, read_cb_f *func,
    void *arg, int require_ctf)
{
	Elf *melf;
	Elf_Cmd cmd = ELF_C_READ;
	Elf_Arhdr *arh;
	int secnum = 1, found = 0;

	while ((melf = elf_begin(fd, cmd, elf)) != NULL) {
		int rc = 0;

		if ((arh = elf_getarhdr(melf)) == NULL) {
			elfterminate(file, "Can't get archive header for "
			    "member %d", secnum);
		}

		/* skip special sections - their names begin with "/" */
		if (*arh->ar_name != '/') {
			size_t memlen = strlen(file) + 1 +
			    strlen(arh->ar_name) + 1 + 1;
			char *memname = xmalloc(memlen);

			snprintf(memname, memlen, "%s(%s)", file, arh->ar_name);

			switch (elf_kind(melf)) {
			case ELF_K_AR:
				rc = read_archive(fd, melf, memname, label,
				    func, arg, require_ctf);
				break;
			case ELF_K_ELF:
				rc = read_file(melf, memname, label,
				    func, arg, require_ctf);
				break;
			default:
				terminate("%s: Unknown elf kind %d\n",
				    memname, elf_kind(melf));
			}

			free(memname);
		}

		cmd = elf_next(melf);
		(void) elf_end(melf);
		secnum++;

		if (rc < 0)
			return (rc);
		else
			found += rc;
	}

	return (found);
}