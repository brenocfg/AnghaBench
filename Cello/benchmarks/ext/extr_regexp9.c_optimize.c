#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {void* end; } ;
struct TYPE_12__ {void* left; TYPE_4__* next; } ;
struct TYPE_11__ {TYPE_5__* cp; void* right; } ;
struct TYPE_14__ {scalar_t__ type; TYPE_2__ u2; TYPE_1__ u1; } ;
struct TYPE_13__ {void* startinst; TYPE_4__* firstinst; } ;
typedef  TYPE_3__ Reprog ;
typedef  TYPE_4__ Reinst ;
typedef  TYPE_5__ Reclass ;

/* Variables and functions */
#define  CCLASS 133 
 scalar_t__ END ; 
#define  NCCLASS 132 
 scalar_t__ NOP ; 
#define  OR 131 
#define  PLUS 130 
#define  QUEST 129 
#define  STAR 128 
 TYPE_4__* freep ; 
 TYPE_3__* realloc (TYPE_3__*,int) ; 

__attribute__((used)) static	Reprog*
optimize(Reprog *pp)
{
	Reinst *inst, *target;
	int size;
	Reprog *npp;
	Reclass *cl;
	int diff;

	/*
	 *  get rid of NOOP chains
	 */
	for(inst=pp->firstinst; inst->type!=END; inst++){
		target = inst->u2.next;
		while(target->type == NOP)
			target = target->u2.next;
		inst->u2.next = target;
	}

	/*
	 *  The original allocation is for an area larger than
	 *  necessary.  Reallocate to the actual space used
	 *  and then relocate the code.
	 */
	size = sizeof(Reprog) + (freep - pp->firstinst)*sizeof(Reinst);
	npp = realloc(pp, size);
	if(npp==0 || npp==pp)
		return pp;
	diff = (char *)npp - (char *)pp;
	freep = (Reinst *)((char *)freep + diff);
	for(inst=npp->firstinst; inst<freep; inst++){
		switch(inst->type){
		case OR:
		case STAR:
		case PLUS:
		case QUEST:
			inst->u1.right = (void*)((char*)inst->u1.right + diff);
			break;
		case CCLASS:
		case NCCLASS:
			inst->u1.right = (void*)((char*)inst->u1.right + diff);
			cl = inst->u1.cp;
			cl->end = (void*)((char*)cl->end + diff);
			break;
		}
		inst->u2.left = (void*)((char*)inst->u2.left + diff);
	}
	npp->startinst = (void*)((char*)npp->startinst + diff);
	return npp;
}