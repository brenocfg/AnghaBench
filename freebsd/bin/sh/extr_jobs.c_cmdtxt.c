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
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {char* text; union node* next; } ;
struct TYPE_14__ {union node* next; } ;
struct TYPE_13__ {union node* redirect; union node* args; } ;
struct TYPE_24__ {union node* com; } ;
struct TYPE_23__ {TYPE_7__* expr; } ;
struct TYPE_20__ {char* var; } ;
struct TYPE_19__ {union node* ch2; union node* ch1; } ;
struct TYPE_18__ {union node* ifpart; union node* test; } ;
struct TYPE_17__ {union node* n; } ;
struct TYPE_16__ {struct nodelist* cmdlist; } ;
union node {int type; TYPE_12__ narg; TYPE_11__ nfile; TYPE_10__ ncmd; TYPE_9__ nnot; TYPE_8__ ncase; TYPE_5__ nfor; TYPE_4__ nbinary; TYPE_3__ nif; TYPE_2__ nredir; TYPE_1__ npipe; } ;
struct nodelist {struct nodelist* next; union node* n; } ;
struct TYPE_21__ {char* text; } ;
struct TYPE_22__ {TYPE_6__ narg; } ;

/* Variables and functions */
#define  NAND 152 
#define  NAPPEND 151 
#define  NARG 150 
#define  NBACKGND 149 
#define  NCASE 148 
#define  NCLOBBER 147 
#define  NCMD 146 
#define  NDEFUN 145 
#define  NFOR 144 
#define  NFROM 143 
#define  NFROMFD 142 
#define  NFROMTO 141 
#define  NHERE 140 
#define  NIF 139 
#define  NNOT 138 
#define  NOR 137 
#define  NPIPE 136 
#define  NREDIR 135 
#define  NSEMI 134 
#define  NSUBSHELL 133 
#define  NTO 132 
#define  NTOFD 131 
#define  NUNTIL 130 
#define  NWHILE 129 
#define  NXHERE 128 
 int /*<<< orphan*/  cmdputs (char*) ; 
 int /*<<< orphan*/  cmdtxtdogroup (union node*) ; 
 int /*<<< orphan*/  cmdtxtredir (union node*,char*,int) ; 

__attribute__((used)) static void
cmdtxt(union node *n)
{
	union node *np;
	struct nodelist *lp;

	if (n == NULL)
		return;
	switch (n->type) {
	case NSEMI:
		cmdtxt(n->nbinary.ch1);
		cmdputs("; ");
		cmdtxt(n->nbinary.ch2);
		break;
	case NAND:
		cmdtxt(n->nbinary.ch1);
		cmdputs(" && ");
		cmdtxt(n->nbinary.ch2);
		break;
	case NOR:
		cmdtxt(n->nbinary.ch1);
		cmdputs(" || ");
		cmdtxt(n->nbinary.ch2);
		break;
	case NPIPE:
		for (lp = n->npipe.cmdlist ; lp ; lp = lp->next) {
			cmdtxt(lp->n);
			if (lp->next)
				cmdputs(" | ");
		}
		break;
	case NSUBSHELL:
		cmdputs("(");
		cmdtxt(n->nredir.n);
		cmdputs(")");
		break;
	case NREDIR:
	case NBACKGND:
		cmdtxt(n->nredir.n);
		break;
	case NIF:
		cmdputs("if ");
		cmdtxt(n->nif.test);
		cmdputs("; then ");
		cmdtxt(n->nif.ifpart);
		cmdputs("...");
		break;
	case NWHILE:
		cmdputs("while ");
		cmdtxt(n->nbinary.ch1);
		cmdtxtdogroup(n->nbinary.ch2);
		break;
	case NUNTIL:
		cmdputs("until ");
		cmdtxt(n->nbinary.ch1);
		cmdtxtdogroup(n->nbinary.ch2);
		break;
	case NFOR:
		cmdputs("for ");
		cmdputs(n->nfor.var);
		cmdputs(" in ...");
		break;
	case NCASE:
		cmdputs("case ");
		cmdputs(n->ncase.expr->narg.text);
		cmdputs(" in ...");
		break;
	case NDEFUN:
		cmdputs(n->narg.text);
		cmdputs("() ...");
		break;
	case NNOT:
		cmdputs("! ");
		cmdtxt(n->nnot.com);
		break;
	case NCMD:
		for (np = n->ncmd.args ; np ; np = np->narg.next) {
			cmdtxt(np);
			if (np->narg.next)
				cmdputs(" ");
		}
		for (np = n->ncmd.redirect ; np ; np = np->nfile.next) {
			cmdputs(" ");
			cmdtxt(np);
		}
		break;
	case NARG:
		cmdputs(n->narg.text);
		break;
	case NTO:
		cmdtxtredir(n, ">", 1);
		break;
	case NAPPEND:
		cmdtxtredir(n, ">>", 1);
		break;
	case NTOFD:
		cmdtxtredir(n, ">&", 1);
		break;
	case NCLOBBER:
		cmdtxtredir(n, ">|", 1);
		break;
	case NFROM:
		cmdtxtredir(n, "<", 0);
		break;
	case NFROMTO:
		cmdtxtredir(n, "<>", 0);
		break;
	case NFROMFD:
		cmdtxtredir(n, "<&", 0);
		break;
	case NHERE:
	case NXHERE:
		cmdputs("<<...");
		break;
	default:
		cmdputs("???");
		break;
	}
}