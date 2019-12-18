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
struct tcpcb {int dummy; } ;
struct tcp_cache_key_src {int dummy; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  tcp_cache_key_src_create (struct tcpcb*,struct tcp_cache_key_src*) ; 
 scalar_t__ tcp_heuristic_do_tfo_common (struct tcp_cache_key_src*) ; 

boolean_t tcp_heuristic_do_tfo(struct tcpcb *tp)
{
	struct tcp_cache_key_src tcks;

	tcp_cache_key_src_create(tp, &tcks);
	if (tcp_heuristic_do_tfo_common(&tcks))
		return (TRUE);

	return (FALSE);
}