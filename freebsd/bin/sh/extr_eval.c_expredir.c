#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  vname; } ;
struct TYPE_4__ {int /*<<< orphan*/  expfname; int /*<<< orphan*/  fname; union node* next; } ;
union node {int type; TYPE_1__ ndup; TYPE_2__ nfile; } ;
struct arglist {int /*<<< orphan*/ * args; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXP_TILDE ; 
#define  NAPPEND 135 
#define  NCLOBBER 134 
#define  NFROM 133 
#define  NFROMFD 132 
#define  NFROMTO 131 
#define  NTO 130 
#define  NTOFD 129 
#define  NXHERE 128 
 int /*<<< orphan*/  emptyarglist (struct arglist*) ; 
 int /*<<< orphan*/  expandarg (int /*<<< orphan*/ ,struct arglist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exphere (union node*,struct arglist*) ; 
 int /*<<< orphan*/  fixredir (union node*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
expredir(union node *n)
{
	union node *redir;

	for (redir = n ; redir ; redir = redir->nfile.next) {
		struct arglist fn;
		emptyarglist(&fn);
		switch (redir->type) {
		case NFROM:
		case NTO:
		case NFROMTO:
		case NAPPEND:
		case NCLOBBER:
			expandarg(redir->nfile.fname, &fn, EXP_TILDE);
			redir->nfile.expfname = fn.args[0];
			break;
		case NFROMFD:
		case NTOFD:
			if (redir->ndup.vname) {
				expandarg(redir->ndup.vname, &fn, EXP_TILDE);
				fixredir(redir, fn.args[0], 1);
			}
			break;
		case NXHERE:
			exphere(redir, &fn);
			break;
		}
	}
}