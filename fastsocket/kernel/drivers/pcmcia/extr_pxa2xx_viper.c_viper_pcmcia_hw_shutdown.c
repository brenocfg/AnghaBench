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
struct soc_pcmcia_socket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIPER_CF_CD_GPIO ; 
 int /*<<< orphan*/  VIPER_CF_POWER_GPIO ; 
 int /*<<< orphan*/  VIPER_CF_RDY_GPIO ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqs ; 
 int /*<<< orphan*/  soc_pcmcia_free_irqs (struct soc_pcmcia_socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void viper_pcmcia_hw_shutdown(struct soc_pcmcia_socket *skt)
{
	soc_pcmcia_free_irqs(skt, irqs, ARRAY_SIZE(irqs));
	gpio_free(VIPER_CF_POWER_GPIO);
	gpio_free(VIPER_CF_RDY_GPIO);
	gpio_free(VIPER_CF_CD_GPIO);
}