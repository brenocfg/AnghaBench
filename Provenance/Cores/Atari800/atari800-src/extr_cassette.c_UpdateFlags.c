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
 scalar_t__ CASSETTE_STATUS_READ_ONLY ; 
 scalar_t__ CASSETTE_STATUS_READ_WRITE ; 
 scalar_t__ CASSETTE_status ; 
 int /*<<< orphan*/  CASSETTE_write_protect ; 
 scalar_t__ cassette_motor ; 
 int cassette_readable ; 
 int cassette_writable ; 
 int /*<<< orphan*/  eof_of_tape ; 

__attribute__((used)) static void UpdateFlags(void)
{
	cassette_readable = cassette_motor &&
	                    (CASSETTE_status == CASSETTE_STATUS_READ_WRITE ||
	                     CASSETTE_status == CASSETTE_STATUS_READ_ONLY) &&
	                     !eof_of_tape;
	cassette_writable = cassette_motor &&
	                    CASSETTE_status == CASSETTE_STATUS_READ_WRITE &&
	                    !CASSETTE_write_protect;
}