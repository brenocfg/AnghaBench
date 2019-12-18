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
struct x25_neigh {int dummy; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 struct sock* __x25_find_socket (unsigned int,struct x25_neigh*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x25_list_lock ; 

struct sock *x25_find_socket(unsigned int lci, struct x25_neigh *nb)
{
	struct sock *s;

	read_lock_bh(&x25_list_lock);
	s = __x25_find_socket(lci, nb);
	read_unlock_bh(&x25_list_lock);
	return s;
}