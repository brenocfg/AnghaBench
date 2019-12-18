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
typedef  int u_char ;
struct sk_buff {int* data; int len; } ;
struct TYPE_2__ {int /*<<< orphan*/  l2m; int /*<<< orphan*/  flag; } ;
struct PStack {TYPE_1__ l2; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_MOD128 ; 
 int /*<<< orphan*/  FLG_ORIG ; 
 int l2addrsize (TYPE_1__*) ; 
 int /*<<< orphan*/  l2m_debug (int /*<<< orphan*/ *,char*,int,int,int,...) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
FRMR_error(struct PStack *st, struct sk_buff *skb)
{
	int headers = l2addrsize(&st->l2) + 1;
	u_char *datap = skb->data + headers;
	int rsp = *skb->data & 0x2;

	if (test_bit(FLG_ORIG, &st->l2.flag))
		rsp = !rsp;

	if (!rsp)
		return 'L';

	if (test_bit(FLG_MOD128, &st->l2.flag)) {
		if (skb->len < headers + 5)
			return 'N';
		else
			l2m_debug(&st->l2.l2m, "FRMR information %2x %2x %2x %2x %2x",
				datap[0], datap[1], datap[2],
				datap[3], datap[4]);
	} else {
		if (skb->len < headers + 3)
			return 'N';
		else
			l2m_debug(&st->l2.l2m, "FRMR information %2x %2x %2x",
				datap[0], datap[1], datap[2]);
	}

	return 0;
}