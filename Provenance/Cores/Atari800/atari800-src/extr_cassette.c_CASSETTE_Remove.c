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
 int /*<<< orphan*/  CASSETTE_STATUS_NONE ; 
 char* CASSETTE_description ; 
 int /*<<< orphan*/  CASSETTE_status ; 
 int /*<<< orphan*/  IMG_TAPE_Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UpdateFlags () ; 
 int /*<<< orphan*/ * cassette_file ; 

void CASSETTE_Remove(void)
{
	if (cassette_file != NULL) {
		IMG_TAPE_Close(cassette_file);
		cassette_file = NULL;
	}
	CASSETTE_status = CASSETTE_STATUS_NONE;
	CASSETTE_description[0] = '\0';
	UpdateFlags();
}