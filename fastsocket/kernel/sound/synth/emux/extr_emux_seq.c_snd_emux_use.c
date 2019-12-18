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
struct snd_seq_port_subscribe {int dummy; } ;
struct snd_emux_port {struct snd_emux* emu; } ;
struct snd_emux {int /*<<< orphan*/  register_mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_emux_inc_count (struct snd_emux*) ; 
 int /*<<< orphan*/  snd_emux_init_port (struct snd_emux_port*) ; 

__attribute__((used)) static int
snd_emux_use(void *private_data, struct snd_seq_port_subscribe *info)
{
	struct snd_emux_port *p;
	struct snd_emux *emu;

	p = private_data;
	if (snd_BUG_ON(!p))
		return -EINVAL;
	emu = p->emu;
	if (snd_BUG_ON(!emu))
		return -EINVAL;

	mutex_lock(&emu->register_mutex);
	snd_emux_init_port(p);
	snd_emux_inc_count(emu);
	mutex_unlock(&emu->register_mutex);
	return 0;
}