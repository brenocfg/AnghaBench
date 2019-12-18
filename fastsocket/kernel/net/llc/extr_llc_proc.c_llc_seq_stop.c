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
struct sock {int dummy; } ;
struct seq_file {int dummy; } ;
struct llc_sock {struct llc_sap* sap; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct llc_sap {TYPE_1__ sk_list; } ;

/* Variables and functions */
 void* SEQ_START_TOKEN ; 
 int /*<<< orphan*/  llc_sap_list_lock ; 
 struct llc_sock* llc_sk (struct sock*) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void llc_seq_stop(struct seq_file *seq, void *v)
{
	if (v && v != SEQ_START_TOKEN) {
		struct sock *sk = v;
		struct llc_sock *llc = llc_sk(sk);
		struct llc_sap *sap = llc->sap;

		read_unlock_bh(&sap->sk_list.lock);
	}
	read_unlock_bh(&llc_sap_list_lock);
}