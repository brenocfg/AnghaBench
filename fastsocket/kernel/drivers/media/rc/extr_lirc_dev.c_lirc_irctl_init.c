#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  minor; } ;
struct irctl {TYPE_1__ d; int /*<<< orphan*/  irctl_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOPLUG ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lirc_irctl_init(struct irctl *ir)
{
	mutex_init(&ir->irctl_lock);
	ir->d.minor = NOPLUG;
}