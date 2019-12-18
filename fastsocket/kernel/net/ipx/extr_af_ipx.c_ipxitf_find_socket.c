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
struct sock {int dummy; } ;
struct ipx_interface {int /*<<< orphan*/  if_sklist_lock; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 struct sock* __ipxitf_find_socket (struct ipx_interface*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sock *ipxitf_find_socket(struct ipx_interface *intrfc,
					__be16 port)
{
	struct sock *s;

	spin_lock_bh(&intrfc->if_sklist_lock);
	s = __ipxitf_find_socket(intrfc, port);
	if (s)
		sock_hold(s);
	spin_unlock_bh(&intrfc->if_sklist_lock);

	return s;
}