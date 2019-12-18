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
typedef  int /*<<< orphan*/  u_char ;
struct sk_buff {scalar_t__* data; } ;
struct l3_process {int /*<<< orphan*/  st; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int CONFIRM ; 
 int DL_ESTABLISH ; 
 scalar_t__ IE_ENDPOINT_ID ; 
 int /*<<< orphan*/  L3DelTimer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  l3_msg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  newl3state (struct l3_process*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l3ni1_spid_epid( struct l3_process *pc, u_char pr, void *arg )
{
	struct sk_buff *skb = arg;

	if ( skb->data[ 1 ] == 0 )
		if ( skb->data[ 3 ] == IE_ENDPOINT_ID )
		{
			L3DelTimer( &pc->timer );
			newl3state( pc, 0 );
			l3_msg( pc->st, DL_ESTABLISH | CONFIRM, NULL );
		}
	dev_kfree_skb( skb);
}