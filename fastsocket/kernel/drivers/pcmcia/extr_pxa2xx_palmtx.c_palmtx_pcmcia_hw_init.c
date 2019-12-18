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
struct soc_pcmcia_socket {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_NR_PALMTX_PCMCIA_POWER1 ; 
 int /*<<< orphan*/  GPIO_NR_PALMTX_PCMCIA_POWER2 ; 
 int /*<<< orphan*/  GPIO_NR_PALMTX_PCMCIA_READY ; 
 int /*<<< orphan*/  GPIO_NR_PALMTX_PCMCIA_RESET ; 
 int gpio_direction_input (int /*<<< orphan*/ ) ; 
 int gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int palmtx_pcmcia_hw_init(struct soc_pcmcia_socket *skt)
{
	int ret;

	ret = gpio_request(GPIO_NR_PALMTX_PCMCIA_POWER1, "PCMCIA PWR1");
	if (ret)
		goto err1;
	ret = gpio_direction_output(GPIO_NR_PALMTX_PCMCIA_POWER1, 0);
	if (ret)
		goto err2;

	ret = gpio_request(GPIO_NR_PALMTX_PCMCIA_POWER2, "PCMCIA PWR2");
	if (ret)
		goto err2;
	ret = gpio_direction_output(GPIO_NR_PALMTX_PCMCIA_POWER2, 0);
	if (ret)
		goto err3;

	ret = gpio_request(GPIO_NR_PALMTX_PCMCIA_RESET, "PCMCIA RST");
	if (ret)
		goto err3;
	ret = gpio_direction_output(GPIO_NR_PALMTX_PCMCIA_RESET, 1);
	if (ret)
		goto err4;

	ret = gpio_request(GPIO_NR_PALMTX_PCMCIA_READY, "PCMCIA RDY");
	if (ret)
		goto err4;
	ret = gpio_direction_input(GPIO_NR_PALMTX_PCMCIA_READY);
	if (ret)
		goto err5;

	skt->irq = gpio_to_irq(GPIO_NR_PALMTX_PCMCIA_READY);
	return 0;

err5:
	gpio_free(GPIO_NR_PALMTX_PCMCIA_READY);
err4:
	gpio_free(GPIO_NR_PALMTX_PCMCIA_RESET);
err3:
	gpio_free(GPIO_NR_PALMTX_PCMCIA_POWER2);
err2:
	gpio_free(GPIO_NR_PALMTX_PCMCIA_POWER1);
err1:
	return ret;
}