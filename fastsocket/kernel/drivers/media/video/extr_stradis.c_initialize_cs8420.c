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
typedef  int /*<<< orphan*/  u8 ;
struct saa7146 {int /*<<< orphan*/  nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2CWrite (struct saa7146*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int INIT8420LEN ; 
 int MODE8420LEN ; 
 int /*<<< orphan*/ * init8420 ; 
 int /*<<< orphan*/ * mode8420con ; 
 int /*<<< orphan*/ * mode8420pro ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void initialize_cs8420(struct saa7146 *saa, int pro)
{
	int i;
	u8 *sequence;
	if (pro)
		sequence = mode8420pro;
	else
		sequence = mode8420con;
	for (i = 0; i < INIT8420LEN; i++)
		I2CWrite(saa, 0x20, init8420[i * 2], init8420[i * 2 + 1], 2);
	for (i = 0; i < MODE8420LEN; i++)
		I2CWrite(saa, 0x20, sequence[i * 2], sequence[i * 2 + 1], 2);
	printk("stradis%d: CS8420 initialized\n", saa->nr);
}