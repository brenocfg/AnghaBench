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
struct sk_buff {int dummy; } ;
struct ip_options {scalar_t__ optlen; } ;
struct TYPE_2__ {struct ip_options opt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 TYPE_1__* IPCB (struct sk_buff*) ; 
 scalar_t__ ip_options_echo (struct ip_options*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_ip_options (struct ip_options*) ; 
 struct ip_options* kmalloc_ip_options (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhel_ip_options_set_alloc_flag (struct ip_options*) ; 

__attribute__((used)) static struct ip_options *tcp_v4_save_options(struct sock *sk,
					      struct sk_buff *skb)
{
	struct ip_options *opt = &(IPCB(skb)->opt);
	struct ip_options *dopt = NULL;

	if (opt && opt->optlen) {
		dopt = kmalloc_ip_options(opt->optlen, GFP_ATOMIC);
		if (dopt) {
			if (ip_options_echo(dopt, skb)) {
				kfree_ip_options(dopt);
				dopt = NULL;
			} else {
				rhel_ip_options_set_alloc_flag(dopt);
			}
		}
	}
	return dopt;
}