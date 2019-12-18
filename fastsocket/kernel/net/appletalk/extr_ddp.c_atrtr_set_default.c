#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ s_node; int /*<<< orphan*/  s_net; } ;
struct TYPE_4__ {TYPE_1__ gateway; int /*<<< orphan*/  flags; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTF_UP ; 
 TYPE_2__ atrtr_default ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atrtr_set_default(struct net_device *dev)
{
	atrtr_default.dev	     = dev;
	atrtr_default.flags	     = RTF_UP;
	atrtr_default.gateway.s_net  = htons(0);
	atrtr_default.gateway.s_node = 0;
}