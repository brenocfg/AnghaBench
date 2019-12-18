#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {union node* ch2; } ;
struct TYPE_5__ {int /*<<< orphan*/ * redirect; union node* n; } ;
struct TYPE_4__ {int backgnd; } ;
union node {scalar_t__ type; TYPE_3__ nbinary; TYPE_2__ nredir; TYPE_1__ npipe; } ;
struct nredir {int dummy; } ;

/* Variables and functions */
 int CHKALIAS ; 
 int CHKKWD ; 
 int CHKNL ; 
 void* NBACKGND ; 
 scalar_t__ NPIPE ; 
 scalar_t__ NREDIR ; 
 int /*<<< orphan*/  NSEMI ; 
#define  TBACKGND 131 
#define  TEOF 130 
#define  TNL 129 
#define  TSEMI 128 
 union node* andor () ; 
 int checkkwd ; 
 int /*<<< orphan*/  heredoclist ; 
 union node* makebinary (int /*<<< orphan*/ ,union node*,union node*) ; 
 int /*<<< orphan*/  parseheredoc () ; 
 size_t peektoken () ; 
 int /*<<< orphan*/  pungetc () ; 
 int readtoken () ; 
 scalar_t__ stalloc (int) ; 
 int /*<<< orphan*/  synexpect (int) ; 
 scalar_t__* tokendlist ; 
 int /*<<< orphan*/  tokpushback ; 

__attribute__((used)) static union node *
list(int nlflag)
{
	union node *ntop, *n1, *n2, *n3;
	int tok;

	checkkwd = CHKNL | CHKKWD | CHKALIAS;
	if (!nlflag && tokendlist[peektoken()])
		return NULL;
	ntop = n1 = NULL;
	for (;;) {
		n2 = andor();
		tok = readtoken();
		if (tok == TBACKGND) {
			if (n2 != NULL && n2->type == NPIPE) {
				n2->npipe.backgnd = 1;
			} else if (n2 != NULL && n2->type == NREDIR) {
				n2->type = NBACKGND;
			} else {
				n3 = (union node *)stalloc(sizeof (struct nredir));
				n3->type = NBACKGND;
				n3->nredir.n = n2;
				n3->nredir.redirect = NULL;
				n2 = n3;
			}
		}
		if (ntop == NULL)
			ntop = n2;
		else if (n1 == NULL) {
			n1 = makebinary(NSEMI, ntop, n2);
			ntop = n1;
		}
		else {
			n3 = makebinary(NSEMI, n1->nbinary.ch2, n2);
			n1->nbinary.ch2 = n3;
			n1 = n3;
		}
		switch (tok) {
		case TBACKGND:
		case TSEMI:
			tok = readtoken();
			/* FALLTHROUGH */
		case TNL:
			if (tok == TNL) {
				parseheredoc();
				if (nlflag)
					return ntop;
			} else if (tok == TEOF && nlflag) {
				parseheredoc();
				return ntop;
			} else {
				tokpushback++;
			}
			checkkwd = CHKNL | CHKKWD | CHKALIAS;
			if (!nlflag && tokendlist[peektoken()])
				return ntop;
			break;
		case TEOF:
			if (heredoclist)
				parseheredoc();
			else
				pungetc();		/* push back EOF on input */
			return ntop;
		default:
			if (nlflag)
				synexpect(-1);
			tokpushback++;
			return ntop;
		}
	}
}