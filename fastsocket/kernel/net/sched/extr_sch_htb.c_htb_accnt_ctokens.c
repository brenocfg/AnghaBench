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
struct htb_class {long ctokens; long cbuffer; long mbuffer; int /*<<< orphan*/  ceil; } ;

/* Variables and functions */
 scalar_t__ qdisc_l2t (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void htb_accnt_ctokens(struct htb_class *cl, int bytes, long diff)
{
	long toks = diff + cl->ctokens;

	if (toks > cl->cbuffer)
		toks = cl->cbuffer;
	toks -= (long) qdisc_l2t(cl->ceil, bytes);
	if (toks <= -cl->mbuffer)
		toks = 1 - cl->mbuffer;

	cl->ctokens = toks;
}