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
struct TYPE_2__ {struct snd_emux_port* channels; } ;
struct snd_emux_port {TYPE_1__ chset; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_emux_port*) ; 
 int /*<<< orphan*/  snd_emux_delete_effect (struct snd_emux_port*) ; 

__attribute__((used)) static void
free_port(void *private_data)
{
	struct snd_emux_port *p;

	p = private_data;
	if (p) {
#ifdef SNDRV_EMUX_USE_RAW_EFFECT
		snd_emux_delete_effect(p);
#endif
		kfree(p->chset.channels);
		kfree(p);
	}
}