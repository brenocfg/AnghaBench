#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int ptype; char** s0num; char** eazlist; int* sil; int* rch; struct TYPE_11__* next; int /*<<< orphan*/  isdnloop_lock; struct TYPE_11__** rcard; } ;
typedef  TYPE_3__ isdnloop_card ;
struct TYPE_9__ {size_t si1; int /*<<< orphan*/  phone; } ;
struct TYPE_10__ {TYPE_1__ setup; } ;
struct TYPE_12__ {TYPE_2__ parm; } ;
typedef  TYPE_4__ isdn_ctrl ;

/* Variables and functions */
#define  ISDN_PTYPE_1TR6 129 
#define  ISDN_PTYPE_EURO 128 
 TYPE_3__* cards ; 
 int /*<<< orphan*/  isdnloop_parse_setup (char*,TYPE_4__*) ; 
 int* si2bit ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
isdnloop_try_call(isdnloop_card * card, char *p, int lch, isdn_ctrl * cmd)
{
	isdnloop_card *cc = cards;
	unsigned long flags;
	int ch;
	int num_match;
	int i;
	char *e;
	char nbuf[32];

	isdnloop_parse_setup(p, cmd);
	while (cc) {
		for (ch = 0; ch < 2; ch++) {
			/* Exclude ourself */
			if ((cc == card) && (ch == lch))
				continue;
			num_match = 0;
			switch (cc->ptype) {
				case ISDN_PTYPE_EURO:
					for (i = 0; i < 3; i++)
						if (!(strcmp(cc->s0num[i], cmd->parm.setup.phone)))
							num_match = 1;
					break;
				case ISDN_PTYPE_1TR6:
					e = cc->eazlist[ch];
					while (*e) {
						sprintf(nbuf, "%s%c", cc->s0num[0], *e);
						if (!(strcmp(nbuf, cmd->parm.setup.phone)))
							num_match = 1;
						e++;
					}
			}
			if (num_match) {
				spin_lock_irqsave(&card->isdnloop_lock, flags);
				/* channel idle? */
				if (!(cc->rcard[ch])) {
					/* Check SI */
					if (!(si2bit[cmd->parm.setup.si1] & cc->sil[ch])) {
						spin_unlock_irqrestore(&card->isdnloop_lock, flags);
						return 3;
					}
					/* ch is idle, si and number matches */
					cc->rcard[ch] = card;
					cc->rch[ch] = lch;
					card->rcard[lch] = cc;
					card->rch[lch] = ch;
					spin_unlock_irqrestore(&card->isdnloop_lock, flags);
					return 0;
				} else {
					spin_unlock_irqrestore(&card->isdnloop_lock, flags);
					/* num matches, but busy */
					if (ch == 1)
						return 1;
				}
			}
		}
		cc = cc->next;
	}
	return 2;
}