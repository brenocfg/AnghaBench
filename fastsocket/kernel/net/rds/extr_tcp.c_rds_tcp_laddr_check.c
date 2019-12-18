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
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 scalar_t__ RTN_LOCAL ; 
 scalar_t__ inet_addr_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 

__attribute__((used)) static int rds_tcp_laddr_check(__be32 addr)
{
	if (inet_addr_type(&init_net, addr) == RTN_LOCAL)
		return 0;
	return -EADDRNOTAVAIL;
}