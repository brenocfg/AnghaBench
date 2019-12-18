#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ip_vs_sync_mesg_v0 {int size; int /*<<< orphan*/  nr_conns; } ;
struct ip_vs_sync_conn_v0 {void* state; void* flags; int /*<<< orphan*/  daddr; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  caddr; int /*<<< orphan*/  dport; int /*<<< orphan*/  vport; int /*<<< orphan*/  cport; int /*<<< orphan*/  protocol; scalar_t__ reserved; } ;
struct ip_vs_sync_conn_options {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  ip; } ;
struct TYPE_8__ {int /*<<< orphan*/  ip; } ;
struct TYPE_7__ {int /*<<< orphan*/  ip; } ;
struct ip_vs_conn {scalar_t__ af; int flags; int state; struct ip_vs_conn* control; int /*<<< orphan*/  in_pkts; int /*<<< orphan*/  in_seq; TYPE_3__ daddr; TYPE_2__ vaddr; TYPE_1__ caddr; int /*<<< orphan*/  dport; int /*<<< orphan*/  vport; int /*<<< orphan*/  cport; int /*<<< orphan*/  protocol; } ;
struct TYPE_10__ {scalar_t__ head; scalar_t__ end; scalar_t__ mesg; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int FULL_CONN_SIZE ; 
 int IP_VS_CONN_F_HASHED ; 
 int IP_VS_CONN_F_ONE_PACKET ; 
 int IP_VS_CONN_F_SEQ_MASK ; 
 int IP_VS_CONN_F_TEMPLATE ; 
 int SIMPLE_CONN_SIZE ; 
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 TYPE_4__* curr_sb ; 
 int /*<<< orphan*/  curr_sb_lock ; 
 void* htons (int) ; 
 TYPE_4__* ip_vs_sync_buff_create_v0 () ; 
 int /*<<< orphan*/  ip_vs_sync_conn (struct ip_vs_conn*,int) ; 
 int /*<<< orphan*/  ip_vs_sync_conn_needed (struct ip_vs_conn*,int) ; 
 int /*<<< orphan*/  memcpy (struct ip_vs_sync_conn_options*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  sb_queue_tail (TYPE_4__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int sysctl_sync_threshold () ; 
 scalar_t__ unlikely (int) ; 

void ip_vs_sync_conn_v0(struct ip_vs_conn *cp, int pkts)
{
	struct ip_vs_sync_mesg_v0 *m;
	struct ip_vs_sync_conn_v0 *s;
	int len;

	if (unlikely(cp->af != AF_INET))
		return;
	/* Do not sync ONE PACKET */
	if (cp->flags & IP_VS_CONN_F_ONE_PACKET)
		return;

	if (!ip_vs_sync_conn_needed(cp, pkts))
		return;
	spin_lock(&curr_sb_lock);
	if (!curr_sb) {
		if (!(curr_sb=ip_vs_sync_buff_create_v0())) {
			spin_unlock(&curr_sb_lock);
			pr_err("ip_vs_sync_buff_create failed.\n");
			return;
		}
	}

	len = (cp->flags & IP_VS_CONN_F_SEQ_MASK) ? FULL_CONN_SIZE :
		SIMPLE_CONN_SIZE;
	m = (struct ip_vs_sync_mesg_v0 *)curr_sb->mesg;
	s = (struct ip_vs_sync_conn_v0 *)curr_sb->head;

	/* copy members */
	s->reserved = 0;
	s->protocol = cp->protocol;
	s->cport = cp->cport;
	s->vport = cp->vport;
	s->dport = cp->dport;
	s->caddr = cp->caddr.ip;
	s->vaddr = cp->vaddr.ip;
	s->daddr = cp->daddr.ip;
	s->flags = htons(cp->flags & ~IP_VS_CONN_F_HASHED);
	s->state = htons(cp->state);
	if (cp->flags & IP_VS_CONN_F_SEQ_MASK) {
		struct ip_vs_sync_conn_options *opt =
			(struct ip_vs_sync_conn_options *)&s[1];
		memcpy(opt, &cp->in_seq, sizeof(*opt));
	}

	m->nr_conns++;
	m->size += len;
	curr_sb->head += len;

	/* check if there is a space for next one */
	if (curr_sb->head + FULL_CONN_SIZE > curr_sb->end) {
		sb_queue_tail(curr_sb);
		curr_sb = NULL;
	}
	spin_unlock(&curr_sb_lock);

	/* synchronize its controller if it has */
	cp = cp->control;
	if (cp) {
		if (cp->flags & IP_VS_CONN_F_TEMPLATE)
			pkts = atomic_add_return(1, &cp->in_pkts);
		else
			pkts = sysctl_sync_threshold();
		ip_vs_sync_conn(cp->control, pkts);
	}
}