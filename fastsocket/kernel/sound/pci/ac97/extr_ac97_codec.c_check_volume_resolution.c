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
struct snd_ac97_res_table {int reg; int bits; } ;
struct snd_ac97 {struct snd_ac97_res_table* res_table; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned short*) ; 
 unsigned short snd_ac97_read (struct snd_ac97*,int) ; 
 int /*<<< orphan*/  snd_ac97_write (struct snd_ac97*,int,int) ; 

__attribute__((used)) static void check_volume_resolution(struct snd_ac97 *ac97, int reg, unsigned char *lo_max, unsigned char *hi_max)
{
	unsigned short cbit[3] = { 0x20, 0x10, 0x01 };
	unsigned char max[3] = { 63, 31, 15 };
	int i;

	/* first look up the static resolution table */
	if (ac97->res_table) {
		const struct snd_ac97_res_table *tbl;
		for (tbl = ac97->res_table; tbl->reg; tbl++) {
			if (tbl->reg == reg) {
				*lo_max = tbl->bits & 0xff;
				*hi_max = (tbl->bits >> 8) & 0xff;
				return;
			}
		}
	}

	*lo_max = *hi_max = 0;
	for (i = 0 ; i < ARRAY_SIZE(cbit); i++) {
		unsigned short val;
		snd_ac97_write(ac97, reg, 0x8080 | cbit[i] | (cbit[i] << 8));
		/* Do the read twice due to buffers on some ac97 codecs.
		 * e.g. The STAC9704 returns exactly what you wrote to the register
		 * if you read it immediately. This causes the detect routine to fail.
		 */
		val = snd_ac97_read(ac97, reg);
		val = snd_ac97_read(ac97, reg);
		if (! *lo_max && (val & 0x7f) == cbit[i])
			*lo_max = max[i];
		if (! *hi_max && ((val >> 8) & 0x7f) == cbit[i])
			*hi_max = max[i];
		if (*lo_max && *hi_max)
			break;
	}
}