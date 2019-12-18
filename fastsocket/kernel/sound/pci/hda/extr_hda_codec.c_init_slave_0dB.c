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
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int get_kctl_0dB_offset (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  put_kctl_with_value (struct snd_kcontrol*,int) ; 

__attribute__((used)) static int init_slave_0dB(void *data, struct snd_kcontrol *slave)
{
	int offset = get_kctl_0dB_offset(slave);
	if (offset > 0)
		put_kctl_with_value(slave, offset);
	return 0;
}