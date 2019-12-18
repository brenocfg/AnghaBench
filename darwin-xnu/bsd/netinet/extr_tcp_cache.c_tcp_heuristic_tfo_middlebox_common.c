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
struct tcp_heuristics_head {int dummy; } ;
struct tcp_heuristic {int dummy; } ;
struct tcp_cache_key_src {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __tcp_heuristic_tfo_middlebox_common (struct tcp_heuristic*) ; 
 struct tcp_heuristic* tcp_getheuristic_with_lock (struct tcp_cache_key_src*,int,struct tcp_heuristics_head**) ; 
 int /*<<< orphan*/  tcp_heuristic_unlock (struct tcp_heuristics_head*) ; 

__attribute__((used)) static void tcp_heuristic_tfo_middlebox_common(struct tcp_cache_key_src *tcks)
{
	struct tcp_heuristics_head *head;
	struct tcp_heuristic *tpheur;

	tpheur = tcp_getheuristic_with_lock(tcks, 1, &head);
	if (tpheur == NULL)
		return;

	__tcp_heuristic_tfo_middlebox_common(tpheur);

	tcp_heuristic_unlock(head);
}