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
struct snd_mpu401 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  outb (unsigned char,unsigned long) ; 

__attribute__((used)) static void mpu401_write_port(struct snd_mpu401 *mpu, unsigned char data,
			      unsigned long addr)
{
	outb(data, addr);
}