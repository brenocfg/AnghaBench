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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  int u_int ;
struct seeprom_config {int dummy; } ;
struct ahd_softc {char channel; int /*<<< orphan*/ * seep_config; } ;
typedef  int /*<<< orphan*/  ahd_mode_state ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_MODE_SCSI ; 
 int EINVAL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int ahd_acquire_seeprom (struct ahd_softc*) ; 
 int ahd_is_paused (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_lock (struct ahd_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahd_pause (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_read_seeprom (struct ahd_softc*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_release_seeprom (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_restore_modes (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_save_modes (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_set_modes (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_unlock (struct ahd_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahd_unpause (struct ahd_softc*) ; 
 int ahd_verify_cksum (struct seeprom_config*) ; 
 int /*<<< orphan*/  ahd_write_seeprom (struct ahd_softc*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
ahd_proc_write_seeprom(struct ahd_softc *ahd, char *buffer, int length)
{
	ahd_mode_state saved_modes;
	int have_seeprom;
	u_long s;
	int paused;
	int written;

	/* Default to failure. */
	written = -EINVAL;
	ahd_lock(ahd, &s);
	paused = ahd_is_paused(ahd);
	if (!paused)
		ahd_pause(ahd);

	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	if (length != sizeof(struct seeprom_config)) {
		printf("ahd_proc_write_seeprom: incorrect buffer size\n");
		goto done;
	}

	have_seeprom = ahd_verify_cksum((struct seeprom_config*)buffer);
	if (have_seeprom == 0) {
		printf("ahd_proc_write_seeprom: cksum verification failed\n");
		goto done;
	}

	have_seeprom = ahd_acquire_seeprom(ahd);
	if (!have_seeprom) {
		printf("ahd_proc_write_seeprom: No Serial EEPROM\n");
		goto done;
	} else {
		u_int start_addr;

		if (ahd->seep_config == NULL) {
			ahd->seep_config = malloc(sizeof(*ahd->seep_config),
						  M_DEVBUF, M_NOWAIT);
			if (ahd->seep_config == NULL) {
				printf("aic79xx: Unable to allocate serial "
				       "eeprom buffer.  Write failing\n");
				goto done;
			}
		}
		printf("aic79xx: Writing Serial EEPROM\n");
		start_addr = 32 * (ahd->channel - 'A');
		ahd_write_seeprom(ahd, (u_int16_t *)buffer, start_addr,
				  sizeof(struct seeprom_config)/2);
		ahd_read_seeprom(ahd, (uint16_t *)ahd->seep_config,
				 start_addr, sizeof(struct seeprom_config)/2,
				 /*ByteStream*/FALSE);
		ahd_release_seeprom(ahd);
		written = length;
	}

done:
	ahd_restore_modes(ahd, saved_modes);
	if (!paused)
		ahd_unpause(ahd);
	ahd_unlock(ahd, &s);
	return (written);
}