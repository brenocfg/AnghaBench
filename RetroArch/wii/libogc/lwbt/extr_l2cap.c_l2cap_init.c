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

/* Variables and functions */
 int /*<<< orphan*/  btmemb_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * l2cap_active_pcbs ; 
 int /*<<< orphan*/ * l2cap_disconnect_bb_cb ; 
 int /*<<< orphan*/ * l2cap_insegs ; 
 int /*<<< orphan*/ * l2cap_listen_pcbs ; 
 int /*<<< orphan*/  l2cap_listenpcbs ; 
 int /*<<< orphan*/  l2cap_pcbs ; 
 int /*<<< orphan*/  l2cap_segs ; 
 int /*<<< orphan*/  l2cap_sigs ; 
 int /*<<< orphan*/ * l2cap_tmp_inseg ; 
 int /*<<< orphan*/ * l2cap_tmp_pcb ; 
 int /*<<< orphan*/ * l2cap_tmp_sig ; 
 int sigid_nxt ; 

void l2cap_init()
{
	btmemb_init(&l2cap_pcbs);
	btmemb_init(&l2cap_listenpcbs);
	btmemb_init(&l2cap_sigs);
	btmemb_init(&l2cap_segs);

	/* Clear globals */
	l2cap_listen_pcbs = NULL;
	l2cap_active_pcbs = NULL;
	l2cap_tmp_pcb = NULL;
	l2cap_tmp_sig = NULL;
	l2cap_insegs = NULL;
	l2cap_tmp_inseg = NULL;
	l2cap_disconnect_bb_cb = NULL;

	/* Initialize the signal identifier (0x00 shall never be used) */
	sigid_nxt = 0x00;
}