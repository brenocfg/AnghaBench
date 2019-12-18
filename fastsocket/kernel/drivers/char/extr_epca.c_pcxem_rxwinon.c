#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct channel {TYPE_1__* board; int /*<<< orphan*/  rxwin; } ;
struct TYPE_2__ {scalar_t__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  outb_p (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pcxem_rxwinon(struct channel *ch)
{
	outb_p(ch->rxwin, (int)ch->board->port + 1);
}