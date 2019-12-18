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
struct sockaddr {int dummy; } ;
struct inpcb {int dummy; } ;

/* Variables and functions */
 scalar_t__ necp_is_intcoproc (struct inpcb*,int /*<<< orphan*/ *) ; 
 scalar_t__ necp_is_loopback (struct sockaddr*,struct sockaddr*,struct inpcb*,int /*<<< orphan*/ *) ; 
 scalar_t__ necp_pass_loopback ; 

__attribute__((used)) static inline bool
necp_socket_bypass(struct sockaddr *override_local_addr, struct sockaddr *override_remote_addr, struct inpcb *inp)
{

	if (necp_pass_loopback > 0 && necp_is_loopback(override_local_addr, override_remote_addr, inp, NULL)) {
		return (true);
	} else if (necp_is_intcoproc(inp, NULL)) {
		return (true);
	}

	return (false);
}