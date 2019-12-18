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
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CORGI_GPIO_MUTE_L ; 
 int /*<<< orphan*/  CORGI_GPIO_MUTE_R ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void corgi_shutdown(struct snd_pcm_substream *substream)
{
	/* set = unmute headphone */
	gpio_set_value(CORGI_GPIO_MUTE_L, 1);
	gpio_set_value(CORGI_GPIO_MUTE_R, 1);
}