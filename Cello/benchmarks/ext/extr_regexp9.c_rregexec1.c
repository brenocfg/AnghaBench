#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_9__ ;
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_21__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_13__ ;
typedef  struct TYPE_26__   TYPE_12__ ;
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
struct TYPE_30__ {scalar_t__ rep; } ;
struct TYPE_28__ {scalar_t__ rsp; } ;
struct TYPE_37__ {TYPE_2__ e; TYPE_1__ s; } ;
struct TYPE_36__ {char r; size_t subid; TYPE_13__* right; TYPE_7__* cp; } ;
struct TYPE_35__ {char* end; char* spans; } ;
struct TYPE_34__ {TYPE_13__* next; } ;
struct TYPE_32__ {char* rep; } ;
struct TYPE_31__ {char* rsp; } ;
struct TYPE_33__ {TYPE_4__ e; TYPE_3__ s; } ;
struct TYPE_29__ {TYPE_5__* m; } ;
struct TYPE_27__ {int type; TYPE_8__ u1; TYPE_6__ u2; } ;
struct TYPE_26__ {scalar_t__ inst; TYPE_21__ se; } ;
struct TYPE_25__ {int startchar; char* rstarts; int starttype; char* reol; TYPE_12__** reliste; TYPE_12__** relist; } ;
struct TYPE_24__ {int /*<<< orphan*/  startinst; } ;
typedef  char Rune ;
typedef  TYPE_9__ Resub ;
typedef  TYPE_10__ Reprog ;
typedef  TYPE_11__ Reljunk ;
typedef  TYPE_12__ Relist ;
typedef  TYPE_13__ Reinst ;

/* Variables and functions */
#define  ANY 138 
#define  ANYNL 137 
#define  BOL 136 
#define  CCLASS 135 
#define  END 134 
#define  EOL 133 
#define  LBRA 132 
#define  NCCLASS 131 
#define  OR 130 
#define  RBRA 129 
#define  RUNE 128 
 int /*<<< orphan*/  _renewmatch (TYPE_9__*,int,TYPE_21__*) ; 
 TYPE_12__* _renewthread (TYPE_12__*,TYPE_13__*,int,TYPE_21__*) ; 
 int /*<<< orphan*/  _rrenewemptythread (TYPE_12__*,int /*<<< orphan*/ ,int,char*) ; 
 char* runestrchr (char*,char) ; 

__attribute__((used)) static int
rregexec1(const Reprog *progp,	/* program to run */
	Rune *bol,		/* string to run machine on */
	Resub *mp,		/* subexpression elements */
	int ms,			/* number of elements at mp */
	Reljunk *j)
{
	int flag=0;
	Reinst *inst;
	Relist *tlp;
	Rune *s;
	int i, checkstart;
	Rune r, *rp, *ep;
	Relist* tl;		/* This list, next list */
	Relist* nl;
	Relist* tle;		/* ends of this and next list */
	Relist* nle;
	int match;
	Rune *p;

	match = 0;
	checkstart = j->startchar;
	if(mp)
		for(i=0; i<ms; i++) {
			mp[i].s.rsp = 0;
			mp[i].e.rep = 0;
		}
	j->relist[0][0].inst = 0;
	j->relist[1][0].inst = 0;

	/* Execute machine once for each character, including terminal NUL */
	s = j->rstarts;
	do{

		/* fast check for first char */
		if(checkstart) {
			switch(j->starttype) {
			case RUNE:
				p = runestrchr(s, j->startchar);
				if(p == 0 || p == j->reol)
					return match;
				s = p;
				break;
			case BOL:
				if(s == bol)
					break;
				p = runestrchr(s, '\n');
				if(p == 0 || s == j->reol)
					return match;
				s = p+1;
				break;
			}
		}

		r = *s;

		/* switch run lists */
		tl = j->relist[flag];
		tle = j->reliste[flag];
		nl = j->relist[flag^=1];
		nle = j->reliste[flag];
		nl->inst = 0;

		/* Add first instruction to current list */
		_rrenewemptythread(tl, progp->startinst, ms, s);

		/* Execute machine until current list is empty */
		for(tlp=tl; tlp->inst; tlp++){
			for(inst=tlp->inst; ; inst = inst->u2.next){
				switch(inst->type){
				case RUNE:	/* regular character */
					if(inst->u1.r == r)
						if(_renewthread(nl, inst->u2.next, ms, &tlp->se)==nle)
							return -1;
					break;
				case LBRA:
					tlp->se.m[inst->u1.subid].s.rsp = s;
					continue;
				case RBRA:
					tlp->se.m[inst->u1.subid].e.rep = s;
					continue;
				case ANY:
					if(r != '\n')
						if(_renewthread(nl, inst->u2.next, ms, &tlp->se)==nle)
							return -1;
					break;
				case ANYNL:
					if(_renewthread(nl, inst->u2.next, ms, &tlp->se)==nle)
							return -1;
					break;
				case BOL:
					if(s == bol || *(s-1) == '\n')
						continue;
					break;
				case EOL:
					if(s == j->reol || r == 0 || r == '\n')
						continue;
					break;
				case CCLASS:
					ep = inst->u1.cp->end;
					for(rp = inst->u1.cp->spans; rp < ep; rp += 2)
						if(r >= rp[0] && r <= rp[1]){
							if(_renewthread(nl, inst->u2.next, ms, &tlp->se)==nle)
								return -1;
							break;
						}
					break;
				case NCCLASS:
					ep = inst->u1.cp->end;
					for(rp = inst->u1.cp->spans; rp < ep; rp += 2)
						if(r >= rp[0] && r <= rp[1])
							break;
					if(rp == ep)
						if(_renewthread(nl, inst->u2.next, ms, &tlp->se)==nle)
							return -1;
					break;
				case OR:
					/* evaluate right choice later */
					if(_renewthread(tlp, inst->u1.right, ms, &tlp->se) == tle)
						return -1;
					/* efficiency: advance and re-evaluate */
					continue;
				case END:	/* Match! */
					match = 1;
					tlp->se.m[0].e.rep = s;
					if(mp != 0)
						_renewmatch(mp, ms, &tlp->se);
					break;
				}
				break;
			}
		}
		if(s == j->reol)
			break;
		checkstart = j->startchar && nl->inst==0;
		s++;
	}while(r);
	return match;
}