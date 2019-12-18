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
struct snd_rawmidi_substream {TYPE_2__* ops; TYPE_1__* runtime; int /*<<< orphan*/  opened; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* trigger ) (struct snd_rawmidi_substream*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct snd_rawmidi_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void snd_rawmidi_output_trigger(struct snd_rawmidi_substream *substream,int up)
{
	if (!substream->opened)
		return;
	if (up) {
		tasklet_schedule(&substream->runtime->tasklet);
	} else {
		tasklet_kill(&substream->runtime->tasklet);
		substream->ops->trigger(substream, 0);
	}
}