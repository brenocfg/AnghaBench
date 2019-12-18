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
typedef  char FLAC__byte ;
typedef  int FLAC__bool ;

/* Variables and functions */
 unsigned int utf8len_ (char const*) ; 

FLAC__bool FLAC__format_vorbiscomment_entry_is_legal(const FLAC__byte *entry, unsigned length)
{
	const FLAC__byte *s, *end;

	for(s = entry, end = s + length; s < end && *s != '='; s++) {
		if(*s < 0x20 || *s > 0x7D)
			return false;
	}
	if(s == end)
		return false;

	s++; /* skip '=' */

	while(s < end) {
		unsigned n = utf8len_(s);
		if(n == 0)
			return false;
		s += n;
	}
	if(s != end)
		return false;

	return true;
}