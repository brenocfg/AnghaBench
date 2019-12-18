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
struct soc_pcmcia_socket {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int GPIO_A0 ; 
 unsigned int GPIO_A1 ; 
 unsigned int GPIO_A2 ; 
 unsigned int GPIO_A3 ; 
 int GRER ; 
 int /*<<< orphan*/  SA1111_DEV (int /*<<< orphan*/ ) ; 
 int sa1111_pcmcia_hw_init (struct soc_pcmcia_socket*) ; 
 int /*<<< orphan*/  sa1111_set_io (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa1111_set_io_dir (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa1111_set_sleep_io (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jornada720_pcmcia_hw_init(struct soc_pcmcia_socket *skt)
{
	unsigned int pin = GPIO_A0 | GPIO_A1 | GPIO_A2 | GPIO_A3;

	/*
	* What is all this crap for?
	*/
	GRER |= 0x00000002;
	/* Set GPIO_A<3:1> to be outputs for PCMCIA/CF power controller: */
	sa1111_set_io_dir(SA1111_DEV(skt->dev), pin, 0, 0);
	sa1111_set_io(SA1111_DEV(skt->dev), pin, 0);
	sa1111_set_sleep_io(SA1111_DEV(skt->dev), pin, 0);

	return sa1111_pcmcia_hw_init(skt);
}