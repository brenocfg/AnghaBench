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
struct cmipci {int chip_version; } ;

/* Variables and functions */
 unsigned int CM_BASE2LIN ; 
 unsigned int CM_CENTR2LIN ; 
 unsigned int CM_REAR2LIN ; 
 int /*<<< orphan*/  CM_REG_LEGACY_CTRL ; 
 int /*<<< orphan*/  CM_REG_MIXER1 ; 
 unsigned int snd_cmipci_read (struct cmipci*,int /*<<< orphan*/ ) ; 
 unsigned int snd_cmipci_read_b (struct cmipci*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int get_line_in_mode(struct cmipci *cm)
{
	unsigned int val;
	if (cm->chip_version >= 39) {
		val = snd_cmipci_read(cm, CM_REG_LEGACY_CTRL);
		if (val & (CM_CENTR2LIN | CM_BASE2LIN))
			return 2;
	}
	val = snd_cmipci_read_b(cm, CM_REG_MIXER1);
	if (val & CM_REAR2LIN)
		return 1;
	return 0;
}