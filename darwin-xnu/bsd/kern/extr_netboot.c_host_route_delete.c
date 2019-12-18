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
struct in_addr {int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTF_HOST ; 
 int /*<<< orphan*/  RTM_DELETE ; 
 int route_cmd (int /*<<< orphan*/ ,struct in_addr,struct in_addr,struct in_addr,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int
host_route_delete(struct in_addr host, unsigned int ifscope)
{
    struct in_addr		zeroes = { 0 };
    
    return (route_cmd(RTM_DELETE, host, zeroes, zeroes, RTF_HOST, ifscope));
}