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
struct ncp_server {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __abort_ncp_connection (struct ncp_server*) ; 

__attribute__((used)) static inline void __ncptcp_abort(struct ncp_server *server)
{
	__abort_ncp_connection(server);
}