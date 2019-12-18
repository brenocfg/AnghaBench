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
typedef  scalar_t__ FLAC__byte ;
typedef  int FLAC__bool ;

/* Variables and functions */
 unsigned int utf8len_ (scalar_t__ const*) ; 

FLAC__bool FLAC__format_vorbiscomment_entry_value_is_legal(const FLAC__byte *value, unsigned length)
{
	if(length == (unsigned)(-1)) {
		while(*value) {
			unsigned n = utf8len_(value);
			if(n == 0)
				return false;
			value += n;
		}
	}
	else {
		const FLAC__byte *end = value + length;
		while(value < end) {
			unsigned n = utf8len_(value);
			if(n == 0)
				return false;
			value += n;
		}
		if(value != end)
			return false;
	}
	return true;
}