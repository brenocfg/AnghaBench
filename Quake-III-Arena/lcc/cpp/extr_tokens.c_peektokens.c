#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* tp; TYPE_2__* bp; TYPE_2__* lp; } ;
typedef  TYPE_1__ Tokenrow ;
struct TYPE_5__ {int* t; size_t len; int /*<<< orphan*/  type; int /*<<< orphan*/  hideset; } ;
typedef  TYPE_2__ Token ;

/* Variables and functions */
 int /*<<< orphan*/  NAME ; 
 int /*<<< orphan*/  NL ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flushout () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  prhideset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void
peektokens(Tokenrow *trp, char *str)
{
	Token *tp;

	tp = trp->tp;
	flushout();
	if (str)
		fprintf(stderr, "%s ", str);
	if (tp<trp->bp || tp>trp->lp)
		fprintf(stderr, "(tp offset %d) ", tp-trp->bp);
	for (tp=trp->bp; tp<trp->lp && tp<trp->bp+32; tp++) {
		if (tp->type!=NL) {
			int c = tp->t[tp->len];
			tp->t[tp->len] = 0;
			fprintf(stderr, "%s", tp->t);
			tp->t[tp->len] = c;
		}
		if (tp->type==NAME) {
			fprintf(stderr, tp==trp->tp?"{*":"{");
			prhideset(tp->hideset);
			fprintf(stderr, "} ");
		} else
			fprintf(stderr, tp==trp->tp?"{%x*} ":"{%x} ", tp->type);
	}
	fprintf(stderr, "\n");
	fflush(stderr);
}