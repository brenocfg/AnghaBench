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
struct snd_emu10k1 {int port; } ;

/* Variables and functions */
 int /*<<< orphan*/  TINA2_VOLUME ; 
 unsigned int inl (unsigned long) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  outl (int,unsigned long) ; 
 int /*<<< orphan*/  snd_emu10k1_ptr20_write (struct snd_emu10k1*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int snd_emu10k1_cardbus_init(struct snd_emu10k1 *emu)
{
	unsigned long special_port;
	unsigned int value;

	/* Special initialisation routine
	 * before the rest of the IO-Ports become active.
	 */
	special_port = emu->port + 0x38;
	value = inl(special_port);
	outl(0x00d00000, special_port);
	value = inl(special_port);
	outl(0x00d00001, special_port);
	value = inl(special_port);
	outl(0x00d0005f, special_port);
	value = inl(special_port);
	outl(0x00d0007f, special_port);
	value = inl(special_port);
	outl(0x0090007f, special_port);
	value = inl(special_port);

	snd_emu10k1_ptr20_write(emu, TINA2_VOLUME, 0, 0xfefefefe); /* Defaults to 0x30303030 */
	/* Delay to give time for ADC chip to switch on. It needs 113ms */
	msleep(200);
	return 0;
}