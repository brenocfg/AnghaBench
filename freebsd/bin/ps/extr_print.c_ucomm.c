#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VARENT ;
struct TYPE_5__ {char* prefix; } ;
struct TYPE_7__ {TYPE_2__* ki_p; TYPE_1__ ki_d; } ;
struct TYPE_6__ {int ki_numthreads; char* ki_tdname; char* ki_moretdname; int /*<<< orphan*/  ki_comm; } ;
typedef  TYPE_3__ KINFO ;

/* Variables and functions */
 int /*<<< orphan*/ * STAILQ_NEXT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asprintf (char**,char*,char*,char*,char*,...) ; 
 int /*<<< orphan*/  next_ve ; 
 scalar_t__ showthreads ; 
 char* strdup (int /*<<< orphan*/ ) ; 

char *
ucomm(KINFO *k, VARENT *ve)
{
	char *str;

	if (STAILQ_NEXT(ve, next_ve) == NULL) {	/* last field, don't pad */
		asprintf(&str, "%s%s%s%s%s",
		    k->ki_d.prefix ? k->ki_d.prefix : "",
		    k->ki_p->ki_comm,
		    (showthreads && k->ki_p->ki_numthreads > 1) ? "/" : "",
		    (showthreads && k->ki_p->ki_numthreads > 1) ? k->ki_p->ki_tdname : "",
		    (showthreads && k->ki_p->ki_numthreads > 1) ? k->ki_p->ki_moretdname : "");
	} else {
		if (showthreads && k->ki_p->ki_numthreads > 1)
			asprintf(&str, "%s/%s%s", k->ki_p->ki_comm,
			    k->ki_p->ki_tdname, k->ki_p->ki_moretdname);
		else
			str = strdup(k->ki_p->ki_comm);
	}
	return (str);
}