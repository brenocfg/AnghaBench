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
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int u_int ;
struct ahd_softc {int /*<<< orphan*/  dev_softc; } ;
typedef  int /*<<< orphan*/  ahd_mode_state ;

/* Variables and functions */
 int /*<<< orphan*/  CLRINT ; 
 int CLRSPLTINT ; 
 int /*<<< orphan*/  DCHSPLTSTAT0 ; 
 int /*<<< orphan*/  DCHSPLTSTAT1 ; 
 int /*<<< orphan*/  PCIXR_STATUS ; 
 int /*<<< orphan*/  SGSPLTSTAT0 ; 
 int /*<<< orphan*/  SGSPLTSTAT1 ; 
 int ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 char* ahd_name (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,int /*<<< orphan*/ ,int) ; 
 int ahd_pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahd_pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ahd_restore_modes (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_save_modes (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_set_modes (struct ahd_softc*,int,int) ; 
 int /*<<< orphan*/  printf (char const*,char*,...) ; 
 char** split_status_source ; 
 char** split_status_strings ; 

__attribute__((used)) static void
ahd_pci_split_intr(struct ahd_softc *ahd, u_int intstat)
{
	uint8_t		split_status[4];
	uint8_t		split_status1[4];
	uint8_t		sg_split_status[2];
	uint8_t		sg_split_status1[2];
	ahd_mode_state	saved_modes;
	u_int		i;
	uint16_t	pcix_status;

	/*
	 * Check for splits in all modes.  Modes 0 and 1
	 * additionally have SG engine splits to look at.
	 */
	pcix_status = ahd_pci_read_config(ahd->dev_softc, PCIXR_STATUS,
					  /*bytes*/2);
	printf("%s: PCI Split Interrupt - PCI-X status = 0x%x\n",
	       ahd_name(ahd), pcix_status);
	saved_modes = ahd_save_modes(ahd);
	for (i = 0; i < 4; i++) {
		ahd_set_modes(ahd, i, i);

		split_status[i] = ahd_inb(ahd, DCHSPLTSTAT0);
		split_status1[i] = ahd_inb(ahd, DCHSPLTSTAT1);
		/* Clear latched errors.  So our interrupt deasserts. */
		ahd_outb(ahd, DCHSPLTSTAT0, split_status[i]);
		ahd_outb(ahd, DCHSPLTSTAT1, split_status1[i]);
		if (i > 1)
			continue;
		sg_split_status[i] = ahd_inb(ahd, SGSPLTSTAT0);
		sg_split_status1[i] = ahd_inb(ahd, SGSPLTSTAT1);
		/* Clear latched errors.  So our interrupt deasserts. */
		ahd_outb(ahd, SGSPLTSTAT0, sg_split_status[i]);
		ahd_outb(ahd, SGSPLTSTAT1, sg_split_status1[i]);
	}

	for (i = 0; i < 4; i++) {
		u_int bit;

		for (bit = 0; bit < 8; bit++) {

			if ((split_status[i] & (0x1 << bit)) != 0) {
				static const char *s;

				s = split_status_strings[bit];
				printf(s, ahd_name(ahd),
				       split_status_source[i]);
			}

			if (i > 1)
				continue;

			if ((sg_split_status[i] & (0x1 << bit)) != 0) {
				static const char *s;

				s = split_status_strings[bit];
				printf(s, ahd_name(ahd), "SG");
			}
		}
	}
	/*
	 * Clear PCI-X status bits.
	 */
	ahd_pci_write_config(ahd->dev_softc, PCIXR_STATUS,
			     pcix_status, /*bytes*/2);
	ahd_outb(ahd, CLRINT, CLRSPLTINT);
	ahd_restore_modes(ahd, saved_modes);
}