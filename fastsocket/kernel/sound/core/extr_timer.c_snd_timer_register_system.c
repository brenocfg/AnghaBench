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
struct TYPE_2__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct snd_timer_system_private {TYPE_1__ tlist; } ;
struct snd_timer {int /*<<< orphan*/  private_free; struct snd_timer_system_private* private_data; int /*<<< orphan*/  hw; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_TIMER_GLOBAL_SYSTEM ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 struct snd_timer_system_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_timer_free (struct snd_timer*) ; 
 int /*<<< orphan*/  snd_timer_free_system ; 
 int snd_timer_global_new (char*,int /*<<< orphan*/ ,struct snd_timer**) ; 
 int snd_timer_global_register (struct snd_timer*) ; 
 int /*<<< orphan*/  snd_timer_s_function ; 
 int /*<<< orphan*/  snd_timer_system ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_timer_register_system(void)
{
	struct snd_timer *timer;
	struct snd_timer_system_private *priv;
	int err;

	err = snd_timer_global_new("system", SNDRV_TIMER_GLOBAL_SYSTEM, &timer);
	if (err < 0)
		return err;
	strcpy(timer->name, "system timer");
	timer->hw = snd_timer_system;
	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (priv == NULL) {
		snd_timer_free(timer);
		return -ENOMEM;
	}
	init_timer(&priv->tlist);
	priv->tlist.function = snd_timer_s_function;
	priv->tlist.data = (unsigned long) timer;
	timer->private_data = priv;
	timer->private_free = snd_timer_free_system;
	return snd_timer_global_register(timer);
}