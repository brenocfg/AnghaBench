#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* f_volname; char* f_localname; char* f_fstype; char* f_opts; TYPE_3__* f_ref; } ;
typedef  TYPE_4__ fsmount ;
struct TYPE_8__ {TYPE_2__* m_dk; } ;
struct TYPE_7__ {TYPE_1__* d_host; } ;
struct TYPE_6__ {int /*<<< orphan*/  h_hostname; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  XFREE (char*) ; 
 int /*<<< orphan*/  domain_strip (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*,char*,char*,char*) ; 
 char* xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
write_ultrix_dkrmount(FILE *ef, char *hn, fsmount *fp)
{
  char *h = xstrdup(fp->f_ref->m_dk->d_host->h_hostname);

  domain_strip(h, hn);
  fprintf(ef, "%s@%s:%s:%s:%s:0:0\n",
	  fp->f_volname,
	  h,
	  fp->f_localname,
	  fp->f_fstype,
	  fp->f_opts);
  XFREE(h);
}