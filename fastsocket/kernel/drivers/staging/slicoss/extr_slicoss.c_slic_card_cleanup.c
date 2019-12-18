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
struct sliccard {int /*<<< orphan*/  loadtimer; scalar_t__ loadtimerset; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct sliccard*) ; 
 int /*<<< orphan*/  slic_debug_card_destroy (struct sliccard*) ; 

__attribute__((used)) static void slic_card_cleanup(struct sliccard *card)
{
	if (card->loadtimerset) {
		card->loadtimerset = 0;
		del_timer(&card->loadtimer);
	}

	slic_debug_card_destroy(card);

	kfree(card);
}