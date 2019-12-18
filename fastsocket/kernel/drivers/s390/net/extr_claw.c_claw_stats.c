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
struct net_device_stats {int dummy; } ;
struct net_device {struct claw_privbk* ml_priv; } ;
struct claw_privbk {struct net_device_stats stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAW_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static struct
net_device_stats *claw_stats(struct net_device *dev)
{
        struct claw_privbk *privptr;

	CLAW_DBF_TEXT(4, trace, "stats");
	privptr = dev->ml_priv;
        return &privptr->stats;
}