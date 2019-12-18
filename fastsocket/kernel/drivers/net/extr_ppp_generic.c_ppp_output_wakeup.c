#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ppp_channel {struct channel* ppp; } ;
struct channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ppp_channel_push (struct channel*) ; 

void
ppp_output_wakeup(struct ppp_channel *chan)
{
	struct channel *pch = chan->ppp;

	if (!pch)
		return;
	ppp_channel_push(pch);
}