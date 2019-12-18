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
struct grip_mp {TYPE_1__** port; } ;
struct gameport {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; scalar_t__ registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  gameport_close (struct gameport*) ; 
 struct grip_mp* gameport_get_drvdata (struct gameport*) ; 
 int /*<<< orphan*/  gameport_set_drvdata (struct gameport*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct grip_mp*) ; 

__attribute__((used)) static void grip_disconnect(struct gameport *gameport)
{
	struct grip_mp *grip = gameport_get_drvdata(gameport);
	int i;

	for (i = 0; i < 4; i++)
		if (grip->port[i]->registered)
			input_unregister_device(grip->port[i]->dev);
	gameport_close(gameport);
	gameport_set_drvdata(gameport, NULL);
	kfree(grip);
}