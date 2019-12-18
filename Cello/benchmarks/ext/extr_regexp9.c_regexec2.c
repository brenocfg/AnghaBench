#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ ** reliste; int /*<<< orphan*/ ** relist; } ;
typedef  int /*<<< orphan*/  Resub ;
typedef  int /*<<< orphan*/  Reprog ;
typedef  TYPE_1__ Reljunk ;
typedef  int /*<<< orphan*/  Relist ;

/* Variables and functions */
 int BIGLISTSIZE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/ * nil ; 
 int regexec1 (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ *,int,TYPE_1__*) ; 

__attribute__((used)) static int
regexec2(const Reprog *progp,	/* program to run */
	char *bol,	/* string to run machine on */
	Resub *mp,	/* subexpression elements */
	int ms,		/* number of elements at mp */
	Reljunk *j
)
{
	int rv;
	Relist *relist0, *relist1;

	/* mark space */
	relist0 = malloc(BIGLISTSIZE*sizeof(Relist));
	if(relist0 == nil)
		return -1;
	relist1 = malloc(BIGLISTSIZE*sizeof(Relist));
	if(relist1 == nil){
		free(relist1);
		return -1;
	}
	j->relist[0] = relist0;
	j->relist[1] = relist1;
	j->reliste[0] = relist0 + BIGLISTSIZE - 2;
	j->reliste[1] = relist1 + BIGLISTSIZE - 2;

	rv = regexec1(progp, bol, mp, ms, j);
	free(relist0);
	free(relist1);
	return rv;
}