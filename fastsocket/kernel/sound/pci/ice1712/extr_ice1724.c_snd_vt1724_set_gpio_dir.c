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
struct snd_ice1712 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_DIRECTION ; 
 int /*<<< orphan*/  ICEREG1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_vt1724_set_gpio_dir(struct snd_ice1712 *ice, unsigned int data)
{
	outl(data, ICEREG1724(ice, GPIO_DIRECTION));
	inw(ICEREG1724(ice, GPIO_DIRECTION)); /* dummy read for pci-posting */
}