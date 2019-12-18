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
struct net_device {scalar_t__ ml_priv; } ;
struct claw_privbk {int tbusy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eieio () ; 

__attribute__((used)) static inline void
claw_set_busy(struct net_device *dev)
{
 ((struct claw_privbk *)dev->ml_priv)->tbusy = 1;
 eieio();
}