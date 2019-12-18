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
struct inet_diag_msg {scalar_t__ idiag_wqueue; scalar_t__ idiag_rqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  dccp_get_info (struct sock*,void*) ; 

__attribute__((used)) static void dccp_diag_get_info(struct sock *sk, struct inet_diag_msg *r,
			       void *_info)
{
	r->idiag_rqueue = r->idiag_wqueue = 0;

	if (_info != NULL)
		dccp_get_info(sk, _info);
}