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
struct gameport {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  kfree (struct gameport*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct gameport* to_gameport_port (struct device*) ; 

__attribute__((used)) static void gameport_release_port(struct device *dev)
{
	struct gameport *gameport = to_gameport_port(dev);

	kfree(gameport);
	module_put(THIS_MODULE);
}