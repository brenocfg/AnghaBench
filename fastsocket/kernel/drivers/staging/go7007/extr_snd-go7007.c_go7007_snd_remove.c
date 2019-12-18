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
struct go7007_snd {int /*<<< orphan*/  card; } ;
struct go7007 {struct go7007_snd* snd_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_card_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_card_free_when_closed (int /*<<< orphan*/ ) ; 

int go7007_snd_remove(struct go7007 *go)
{
	struct go7007_snd *gosnd = go->snd_context;

	snd_card_disconnect(gosnd->card);
	snd_card_free_when_closed(gosnd->card);
	return 0;
}