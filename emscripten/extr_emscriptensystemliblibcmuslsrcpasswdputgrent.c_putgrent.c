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
struct group {char* gr_name; char* gr_passwd; int gr_gid; scalar_t__* gr_mem; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  flockfile (int /*<<< orphan*/ *) ; 
 int fprintf (int /*<<< orphan*/ *,char*,char*,char*,...) ; 
 int fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  funlockfile (int /*<<< orphan*/ *) ; 

int putgrent(const struct group *gr, FILE *f)
{
	int r;
	size_t i;
	flockfile(f);
	if ((r = fprintf(f, "%s:%s:%d:", gr->gr_name, gr->gr_passwd, gr->gr_gid))<0) goto done;
	if (gr->gr_mem) for (i=0; gr->gr_mem[i]; i++)
		if ((r = fprintf(f, "%s%s", i?",":"", gr->gr_mem[i]))<0) goto done;
	r = fputc('\n', f);
done:
	funlockfile(f);
	return r<0 ? -1 : 0;
}