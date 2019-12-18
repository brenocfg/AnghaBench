#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {char* starts; scalar_t__ startchar; int /*<<< orphan*/ ** reliste; int /*<<< orphan*/ ** relist; scalar_t__ starttype; scalar_t__ eol; } ;
struct TYPE_21__ {TYPE_4__* startinst; } ;
struct TYPE_17__ {scalar_t__ ep; } ;
struct TYPE_16__ {char* sp; } ;
struct TYPE_20__ {TYPE_2__ e; TYPE_1__ s; } ;
struct TYPE_18__ {scalar_t__ r; } ;
struct TYPE_19__ {scalar_t__ type; TYPE_3__ u1; } ;
typedef  TYPE_5__ Resub ;
typedef  TYPE_6__ Reprog ;
typedef  TYPE_7__ Reljunk ;
typedef  int /*<<< orphan*/  Relist ;

/* Variables and functions */
 scalar_t__ BOL ; 
 int LISTSIZE ; 
 scalar_t__ RUNE ; 
 scalar_t__ Runeself ; 
 int nelem (int /*<<< orphan*/ *) ; 
 int regexec1 (TYPE_6__ const*,char*,TYPE_5__*,int,TYPE_7__*) ; 
 int regexec2 (TYPE_6__ const*,char*,TYPE_5__*,int,TYPE_7__*) ; 

extern int
regexec9(const Reprog *progp,	/* program to run */
	char *bol,	/* string to run machine on */
	Resub *mp,	/* subexpression elements */
	int ms)		/* number of elements at mp */
{
	Reljunk j;
	Relist relist0[LISTSIZE], relist1[LISTSIZE];
	int rv;

	/*
 	 *  use user-specified starting/ending location if specified
	 */
	j.starts = bol;
	j.eol = 0;
	if(mp && ms>0){
		if(mp->s.sp)
			j.starts = mp->s.sp;
		if(mp->e.ep)
			j.eol = mp->e.ep;
	}
	j.starttype = 0;
	j.startchar = 0;
	if(progp->startinst->type == RUNE && progp->startinst->u1.r < Runeself) {
		j.starttype = RUNE;
		j.startchar = progp->startinst->u1.r;
	}
	if(progp->startinst->type == BOL)
		j.starttype = BOL;

	/* mark space */
	j.relist[0] = relist0;
	j.relist[1] = relist1;
	j.reliste[0] = relist0 + nelem(relist0) - 2;
	j.reliste[1] = relist1 + nelem(relist1) - 2;

	rv = regexec1(progp, bol, mp, ms, &j);
	if(rv >= 0)
		return rv;
	rv = regexec2(progp, bol, mp, ms, &j);
	if(rv >= 0)
		return rv;
	return -1;
}