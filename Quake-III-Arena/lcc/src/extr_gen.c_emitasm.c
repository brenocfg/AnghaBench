#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_1__** kids; scalar_t__ emitted; } ;
struct TYPE_21__ {char** kids; TYPE_13__** syms; TYPE_2__ x; } ;
struct TYPE_20__ {int /*<<< orphan*/  name; } ;
struct TYPE_19__ {short** _nts; char** _templates; int /*<<< orphan*/  (* _kids ) (TYPE_5__*,int,TYPE_5__**) ;int /*<<< orphan*/  (* emit2 ) (TYPE_5__*) ;scalar_t__* _isinstruction; } ;
struct TYPE_17__ {TYPE_13__** syms; } ;
struct TYPE_16__ {TYPE_3__ x; } ;
struct TYPE_15__ {TYPE_4__ x; } ;
typedef  TYPE_5__* Node ;

/* Variables and functions */
 TYPE_14__* IR ; 
 char NELEMS (TYPE_13__**) ; 
 size_t RX ; 
 int /*<<< orphan*/  assert (char*) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  framesize ; 
 int getrule (TYPE_5__*,int) ; 
 int /*<<< orphan*/  print (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putchar (char) ; 
 TYPE_5__* reuse (TYPE_5__*,int) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int,TYPE_5__**) ; 

__attribute__((used)) static unsigned emitasm(Node p, int nt) {
	int rulenum;
	short *nts;
	char *fmt;
	Node kids[10];

	p = reuse(p, nt);
	rulenum = getrule(p, nt);
	nts = IR->x._nts[rulenum];
	fmt = IR->x._templates[rulenum];
	assert(fmt);
	if (IR->x._isinstruction[rulenum] && p->x.emitted)
		print("%s", p->syms[RX]->x.name);
	else if (*fmt == '#')
		(*IR->x.emit2)(p);
	else {
		if (*fmt == '?') {
			fmt++;
			assert(p->kids[0]);
			if (p->syms[RX] == p->x.kids[0]->syms[RX])
				while (*fmt++ != '\n')
					;
		}
		for ((*IR->x._kids)(p, rulenum, kids); *fmt; fmt++)
			if (*fmt != '%')
				(void)putchar(*fmt);
			else if (*++fmt == 'F')
				print("%d", framesize);
			else if (*fmt >= '0' && *fmt <= '9')
				emitasm(kids[*fmt - '0'], nts[*fmt - '0']);
			else if (*fmt >= 'a' && *fmt < 'a' + NELEMS(p->syms))
				fputs(p->syms[*fmt - 'a']->x.name, stdout);
			else
				(void)putchar(*fmt);
	}
	return 0;
}