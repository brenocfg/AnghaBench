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

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void user_education(void)
{
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "\teeprom_fix FW-FILE SWITCH [ADDRESS [VALUE MASK]]\n");

	fprintf(stderr, "\nDescription:\n");
	fprintf(stderr, "\tThis utility manage a set of overrides which "
			"commands the driver\n\tto load customized EEPROM' "
			"data for all specified addresses.\n");

	fprintf(stderr, "\nParameters:\n");
	fprintf(stderr, "\t'FW-FILE'  = firmware file [basename]\n");
	fprintf(stderr, "\t'SWITCH'   = [=|d|D]\n");
	fprintf(stderr, "\t | '='       => add/set value for address\n");
	fprintf(stderr, "\t | 'D'       => removes all EEPROM overrides\n");
	fprintf(stderr, "\t * 'd'       => removed override for 'address'\n");
	fprintf(stderr, "\n\t'ADDRESS'  = location of the EEPROM override\n");
	fprintf(stderr, "\t\t     NB: must be a multiple of 4.\n");
	fprintf(stderr, "\t\t     an address map can be found in eeprom.h.\n");
	fprintf(stderr, "\n\t'VALUE'    = replacement value\n");
	fprintf(stderr, "\t'MASK'     = mask for the value placement.\n\n");

	exit(EXIT_FAILURE);
}