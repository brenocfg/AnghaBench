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
struct mbuf {int dummy; } ;

/* Variables and functions */
 scalar_t__ necp_get_is_keepalive_from_packet (struct mbuf*) ; 
 scalar_t__ necp_is_intcoproc (int /*<<< orphan*/ *,struct mbuf*) ; 
 scalar_t__ necp_is_loopback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct mbuf*) ; 
 scalar_t__ necp_pass_keepalives ; 
 scalar_t__ necp_pass_loopback ; 

__attribute__((used)) static inline bool
necp_output_bypass(struct mbuf *packet)
{
	if (necp_pass_loopback > 0 && necp_is_loopback(NULL, NULL, NULL, packet)) {
		return (true);
	}
	if (necp_pass_keepalives > 0 && necp_get_is_keepalive_from_packet(packet)) {
		return (true);
	}
	if (necp_is_intcoproc(NULL, packet)) {
		return (true);
	}
	return (false);
}