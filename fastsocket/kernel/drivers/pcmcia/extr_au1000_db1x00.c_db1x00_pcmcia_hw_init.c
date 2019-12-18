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
struct au1000_pcmcia_socket {scalar_t__ nr; void* irq; } ;

/* Variables and functions */
 void* AU1000_GPIO_2 ; 
 void* AU1000_GPIO_3 ; 
 void* AU1000_GPIO_5 ; 
 void* BOARD_PC0_INT ; 
 void* BOARD_PC1_INT ; 

__attribute__((used)) static int db1x00_pcmcia_hw_init(struct au1000_pcmcia_socket *skt)
{
#ifdef CONFIG_MIPS_DB1550
	skt->irq = skt->nr ? AU1000_GPIO_5 : AU1000_GPIO_3;
#elif defined(CONFIG_MIPS_DB1200) || defined(CONFIG_MIPS_PB1200)
	skt->irq = skt->nr ? BOARD_PC1_INT : BOARD_PC0_INT;
#else
	skt->irq = skt->nr ? AU1000_GPIO_5 : AU1000_GPIO_2;
#endif
	return 0;
}