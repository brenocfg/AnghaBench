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
struct spi_device {int dummy; } ;
struct lms283gf05_seq {char reg; int value; int /*<<< orphan*/  delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_write (struct spi_device*,char*,int) ; 

__attribute__((used)) static void lms283gf05_toggle(struct spi_device *spi,
			struct lms283gf05_seq *seq, int sz)
{
	char buf[3];
	int i;

	for (i = 0; i < sz; i++) {
		buf[0] = 0x74;
		buf[1] = 0x00;
		buf[2] = seq[i].reg;
		spi_write(spi, buf, 3);

		buf[0] = 0x76;
		buf[1] = seq[i].value >> 8;
		buf[2] = seq[i].value & 0xff;
		spi_write(spi, buf, 3);

		mdelay(seq[i].delay);
	}
}