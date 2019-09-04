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
struct tcp_heuristic {scalar_t__ th_tfo_in_backoff; int /*<<< orphan*/  th_tfo_enabled_time; int /*<<< orphan*/  th_tfo_backoff_until; } ;
struct tcp_cache_key_src {int dummy; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ TSTMP_GT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ disable_tcp_heuristics ; 
 struct tcp_heuristic* tcp_getheuristic_with_lock (struct tcp_cache_key_src*,int /*<<< orphan*/ ,struct tcp_heuristics_head**) ; 
 int /*<<< orphan*/  tcp_heuristic_unlock (struct tcp_heuristics_head*) ; 
 int /*<<< orphan*/  tcp_now ; 

__attribute__((used)) static boolean_t tcp_heuristic_do_tfo_common(struct tcp_cache_key_src *tcks)
{
	struct tcp_heuristics_head *head;
	struct tcp_heuristic *tpheur;

	if (disable_tcp_heuristics)
		return (TRUE);

	/* Get the tcp-heuristic. */
	tpheur = tcp_getheuristic_with_lock(tcks, 0, &head);
	if (tpheur == NULL)
		return (TRUE);

	if (tpheur->th_tfo_in_backoff == 0)
		goto tfo_ok;

	if (TSTMP_GT(tcp_now, tpheur->th_tfo_backoff_until)) {
		tpheur->th_tfo_in_backoff = 0;
		tpheur->th_tfo_enabled_time = tcp_now;

		goto tfo_ok;
	}

	tcp_heuristic_unlock(head);
	return (FALSE);

tfo_ok:
	tcp_heuristic_unlock(head);
	return (TRUE);
}