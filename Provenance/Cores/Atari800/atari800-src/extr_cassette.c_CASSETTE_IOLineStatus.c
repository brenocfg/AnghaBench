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
 scalar_t__ CASSETTE_record ; 
 int IMG_TAPE_SerinStatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cassette_file ; 
 int /*<<< orphan*/  cassette_readable ; 
 int /*<<< orphan*/  event_time_left ; 
 scalar_t__ passing_gap ; 

int CASSETTE_IOLineStatus(void)
{
	/* if motor off and EOF return always 1 (equivalent the mark tone) */
	if (!cassette_readable || CASSETTE_record || passing_gap) {
		return 1;
	}

	return IMG_TAPE_SerinStatus(cassette_file, event_time_left);
}