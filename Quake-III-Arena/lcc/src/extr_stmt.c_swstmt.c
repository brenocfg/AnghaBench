#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct swtch {int lab; scalar_t__ ncases; TYPE_9__* deflab; void* labels; void* values; int /*<<< orphan*/  size; TYPE_8__* sym; } ;
typedef  TYPE_4__* Tree ;
struct TYPE_24__ {scalar_t__ ref; } ;
struct TYPE_23__ {scalar_t__ type; } ;
struct TYPE_22__ {TYPE_3__* next; struct TYPE_22__* prev; } ;
struct TYPE_21__ {scalar_t__ type; TYPE_2__** kids; int /*<<< orphan*/  op; } ;
struct TYPE_20__ {TYPE_5__* prev; } ;
struct TYPE_18__ {TYPE_8__* sym; } ;
struct TYPE_19__ {TYPE_1__ u; int /*<<< orphan*/  op; } ;
typedef  TYPE_5__* Code ;

/* Variables and functions */
 int /*<<< orphan*/  FUNC ; 
 scalar_t__ INDIR ; 
 int /*<<< orphan*/  REGISTER ; 
 int /*<<< orphan*/  SWSIZE ; 
 int /*<<< orphan*/  Switch ; 
 int /*<<< orphan*/  addlocal (TYPE_8__*) ; 
 int /*<<< orphan*/ * asgn (TYPE_8__*,TYPE_4__*) ; 
 int /*<<< orphan*/  branch (int) ; 
 TYPE_4__* cast (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* code (int /*<<< orphan*/ ) ; 
 TYPE_5__* codelist ; 
 int /*<<< orphan*/  definelab (int) ; 
 int /*<<< orphan*/  definept (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 int /*<<< orphan*/  expect (char) ; 
 TYPE_4__* expr (char) ; 
 TYPE_9__* findlabel (int) ; 
 scalar_t__ generic (int /*<<< orphan*/ ) ; 
 TYPE_8__* genident (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gettok () ; 
 int /*<<< orphan*/  inttype ; 
 scalar_t__ isaddrop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isint (scalar_t__) ; 
 int /*<<< orphan*/  isvolatile (scalar_t__) ; 
 int /*<<< orphan*/  level ; 
 void* newarray (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  promote (scalar_t__) ; 
 double refinc ; 
 TYPE_4__* retype (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  statement (int,struct swtch*,int) ; 
 int /*<<< orphan*/  swgen (struct swtch*) ; 
 int /*<<< orphan*/  t ; 
 int /*<<< orphan*/  walk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static void swstmt(int loop, int lab, int lev) {
	Tree e;
	struct swtch sw;
	Code head, tail;

	t = gettok();
	expect('(');
	definept(NULL);
	e = expr(')');
	if (!isint(e->type)) {
		error("illegal type `%t' in switch expression\n",
			e->type);
		e = retype(e, inttype);
	}
	e = cast(e, promote(e->type));
	if (generic(e->op) == INDIR && isaddrop(e->kids[0]->op)
	&& e->kids[0]->u.sym->type == e->type
	&& !isvolatile(e->kids[0]->u.sym->type)) {
		sw.sym = e->kids[0]->u.sym;
		walk(NULL, 0, 0);
	} else {
		sw.sym = genident(REGISTER, e->type, level);
		addlocal(sw.sym);
		walk(asgn(sw.sym, e), 0, 0);
	}
	head = code(Switch);
	sw.lab = lab;
	sw.deflab = NULL;
	sw.ncases = 0;
	sw.size = SWSIZE;
	sw.values = newarray(SWSIZE, sizeof *sw.values, FUNC);
	sw.labels = newarray(SWSIZE, sizeof *sw.labels, FUNC);
	refinc /= 10.0;
	statement(loop, &sw, lev);
	if (sw.deflab == NULL) {
		sw.deflab = findlabel(lab);
		definelab(lab);
		if (sw.ncases == 0)
			warning("switch statement with no cases\n");
	}
	if (findlabel(lab + 1)->ref)
		definelab(lab + 1);
	tail = codelist;
	codelist = head->prev;
	codelist->next = head->prev = NULL;
	if (sw.ncases > 0)
		swgen(&sw);
	branch(lab);
	head->next->prev = codelist;
	codelist->next = head->next;
	codelist = tail;
}