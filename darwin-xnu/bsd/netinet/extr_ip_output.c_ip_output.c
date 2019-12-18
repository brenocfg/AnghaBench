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
struct route {int dummy; } ;
struct mbuf {int dummy; } ;
struct ip_out_args {int dummy; } ;
struct ip_moptions {int dummy; } ;

/* Variables and functions */
 int ip_output_list (struct mbuf*,int /*<<< orphan*/ ,struct mbuf*,struct route*,int,struct ip_moptions*,struct ip_out_args*) ; 

int
ip_output(struct mbuf *m0, struct mbuf *opt, struct route *ro, int flags,
    struct ip_moptions *imo, struct ip_out_args *ipoa)
{
	return (ip_output_list(m0, 0, opt, ro, flags, imo, ipoa));
}