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
typedef  int /*<<< orphan*/  u_int32_t ;
struct necp_socket_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  necp_kernel_socket_policies_gencount ; 
 int /*<<< orphan*/  net_flowhash (struct necp_socket_info*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u_int32_t
necp_socket_calc_flowhash_locked(struct necp_socket_info *info)
{
	return (net_flowhash(info, sizeof(*info), necp_kernel_socket_policies_gencount));
}