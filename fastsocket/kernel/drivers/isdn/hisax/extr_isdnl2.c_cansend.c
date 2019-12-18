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
struct TYPE_2__ {int vs; int va; unsigned int window; int /*<<< orphan*/  flag; } ;
struct PStack {TYPE_1__ l2; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_MOD128 ; 
 int /*<<< orphan*/  FLG_PEER_BUSY ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline unsigned int
cansend(struct PStack *st)
{
	unsigned int p1;

	if(test_bit(FLG_MOD128, &st->l2.flag))
		p1 = (st->l2.vs - st->l2.va) % 128;
	else
		p1 = (st->l2.vs - st->l2.va) % 8;
	return ((p1 < st->l2.window) && !test_bit(FLG_PEER_BUSY, &st->l2.flag));
}