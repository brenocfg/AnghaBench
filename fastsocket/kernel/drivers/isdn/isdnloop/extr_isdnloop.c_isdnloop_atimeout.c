#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* rch; int /*<<< orphan*/  isdnloop_lock; struct TYPE_5__** rcard; } ;
typedef  TYPE_1__ isdnloop_card ;

/* Variables and functions */
 int /*<<< orphan*/  isdnloop_fake (TYPE_1__*,char*,int) ; 
 char* isdnloop_unicause (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static void
isdnloop_atimeout(isdnloop_card * card, int ch)
{
	unsigned long flags;
	char buf[60];

	spin_lock_irqsave(&card->isdnloop_lock, flags);
	if (card->rcard) {
		isdnloop_fake(card->rcard[ch], "DDIS_I", card->rch[ch] + 1);
		card->rcard[ch]->rcard[card->rch[ch]] = NULL;
		card->rcard[ch] = NULL;
	}
	isdnloop_fake(card, "DDIS_I", ch + 1);
	/* No user responding */
	sprintf(buf, "CAU%s", isdnloop_unicause(card, 1, 3));
	isdnloop_fake(card, buf, ch + 1);
	spin_unlock_irqrestore(&card->isdnloop_lock, flags);
}