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
typedef  long u32 ;
struct snd_au1000 {int /*<<< orphan*/  ac97_lock; TYPE_1__* ac97_ioport; } ;
struct TYPE_2__ {long config; } ;

/* Variables and functions */
 long AC97C_RECV_SLOTS_BIT ; 
 long volatile AC97C_RECV_SLOTS_MASK ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
au1000_set_ac97_recv_slots(struct snd_au1000 *au1000, long recv_slots)
{
	u32 volatile ac97_config;

	spin_lock(&au1000->ac97_lock);
	ac97_config = au1000->ac97_ioport->config;
	ac97_config = ac97_config & ~AC97C_RECV_SLOTS_MASK;
	ac97_config |= (recv_slots << AC97C_RECV_SLOTS_BIT);
	au1000->ac97_ioport->config = ac97_config;
	spin_unlock(&au1000->ac97_lock);
}