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
struct snd_info_entry {scalar_t__ private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct snd_ice1712 {int /*<<< orphan*/  gpio_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_DEV ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,int,int) ; 
 int spi_read (struct snd_ice1712*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cs_proc_regs_read(struct snd_info_entry *entry, struct snd_info_buffer *buffer)
{
	struct snd_ice1712 *ice = (struct snd_ice1712 *)entry->private_data;
	int reg, val;

	mutex_lock(&ice->gpio_mutex);
	for (reg = 0; reg <= 0x26; reg++) {
		val = spi_read(ice, CS_DEV, reg);
		snd_iprintf(buffer, "%02x = %02x\n", reg, val);
	}
	val = spi_read(ice, CS_DEV, 0x7f);
	snd_iprintf(buffer, "%02x = %02x\n", 0x7f, val);
	mutex_unlock(&ice->gpio_mutex);
}