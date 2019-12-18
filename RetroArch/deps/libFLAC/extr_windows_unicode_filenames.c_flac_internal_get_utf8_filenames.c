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
typedef  int /*<<< orphan*/  FLAC__bool ;

/* Variables and functions */
 int /*<<< orphan*/  utf8_filenames ; 

FLAC__bool flac_internal_get_utf8_filenames(void)
{
	return utf8_filenames;
}