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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ CASSETTE_STATUS_NONE ; 
 char* CASSETTE_filename ; 
 scalar_t__ CASSETTE_status ; 
 int CASSETTE_write_protect ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

void CASSETTE_WriteConfig(FILE *fp)
{
	fprintf(fp, "CASSETTE_FILENAME=%s\n", CASSETTE_filename);
	fprintf(fp, "CASSETTE_LOADED=%d\n", CASSETTE_status != CASSETTE_STATUS_NONE);
	fprintf(fp, "CASSETTE_WRITE_PROTECT=%d\n", CASSETTE_write_protect);
}