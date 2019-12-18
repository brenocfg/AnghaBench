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
struct inode {struct ath_softc* i_private; } ;
struct file {int /*<<< orphan*/ * private_data; } ;
struct ath_softc {int /*<<< orphan*/  sc_ah; } ;

/* Variables and functions */
 scalar_t__ AR_SREV_9300_20_OR_LATER (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 unsigned long REGDUMP_LINE_SIZE ; 
 int /*<<< orphan*/  REG_READ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath9k_ps_restore (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 
 scalar_t__ scnprintf (int /*<<< orphan*/ *,unsigned long,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vmalloc (unsigned long) ; 

__attribute__((used)) static int open_file_regdump(struct inode *inode, struct file *file)
{
	struct ath_softc *sc = inode->i_private;
	unsigned int len = 0;
	u8 *buf;
	int i;
	unsigned long num_regs, regdump_len, max_reg_offset;

	max_reg_offset = AR_SREV_9300_20_OR_LATER(sc->sc_ah) ? 0x16bd4 : 0xb500;
	num_regs = max_reg_offset / 4 + 1;
	regdump_len = num_regs * REGDUMP_LINE_SIZE + 1;
	buf = vmalloc(regdump_len);
	if (!buf)
		return -ENOMEM;

	ath9k_ps_wakeup(sc);
	for (i = 0; i < num_regs; i++)
		len += scnprintf(buf + len, regdump_len - len,
			"0x%06x 0x%08x\n", i << 2, REG_READ(sc->sc_ah, i << 2));
	ath9k_ps_restore(sc);

	file->private_data = buf;

	return 0;
}