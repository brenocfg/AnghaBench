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
typedef  int FLAC__bool ;

/* Variables and functions */

FLAC__bool FLAC__format_vorbiscomment_entry_name_is_legal(const char *name)
{
	char c;
	for(c = *name; c; c = *(++name))
		if(c < 0x20 || c == 0x3d || c > 0x7d)
			return false;
	return true;
}