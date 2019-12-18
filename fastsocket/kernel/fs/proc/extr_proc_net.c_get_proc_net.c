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
struct net {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDE (struct inode const*) ; 
 int /*<<< orphan*/  PDE_NET (int /*<<< orphan*/ ) ; 
 struct net* maybe_get_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct net *get_proc_net(const struct inode *inode)
{
	return maybe_get_net(PDE_NET(PDE(inode)));
}