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
typedef  int FLAC__byte ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__ASSERT (int) ; 

__attribute__((used)) static unsigned utf8len_(const FLAC__byte *utf8)
{
	FLAC__ASSERT(0 != utf8);
	if ((utf8[0] & 0x80) == 0) {
		return 1;
	}
	else if ((utf8[0] & 0xE0) == 0xC0 && (utf8[1] & 0xC0) == 0x80) {
		if ((utf8[0] & 0xFE) == 0xC0) /* overlong sequence check */
			return 0;
		return 2;
	}
	else if ((utf8[0] & 0xF0) == 0xE0 && (utf8[1] & 0xC0) == 0x80 && (utf8[2] & 0xC0) == 0x80) {
		if (utf8[0] == 0xE0 && (utf8[1] & 0xE0) == 0x80) /* overlong sequence check */
			return 0;
		/* illegal surrogates check (U+D800...U+DFFF and U+FFFE...U+FFFF) */
		if (utf8[0] == 0xED && (utf8[1] & 0xE0) == 0xA0) /* D800-DFFF */
			return 0;
		if (utf8[0] == 0xEF && utf8[1] == 0xBF && (utf8[2] & 0xFE) == 0xBE) /* FFFE-FFFF */
			return 0;
		return 3;
	}
	else if ((utf8[0] & 0xF8) == 0xF0 && (utf8[1] & 0xC0) == 0x80 && (utf8[2] & 0xC0) == 0x80 && (utf8[3] & 0xC0) == 0x80) {
		if (utf8[0] == 0xF0 && (utf8[1] & 0xF0) == 0x80) /* overlong sequence check */
			return 0;
		return 4;
	}
	else if ((utf8[0] & 0xFC) == 0xF8 && (utf8[1] & 0xC0) == 0x80 && (utf8[2] & 0xC0) == 0x80 && (utf8[3] & 0xC0) == 0x80 && (utf8[4] & 0xC0) == 0x80) {
		if (utf8[0] == 0xF8 && (utf8[1] & 0xF8) == 0x80) /* overlong sequence check */
			return 0;
		return 5;
	}
	else if ((utf8[0] & 0xFE) == 0xFC && (utf8[1] & 0xC0) == 0x80 && (utf8[2] & 0xC0) == 0x80 && (utf8[3] & 0xC0) == 0x80 && (utf8[4] & 0xC0) == 0x80 && (utf8[5] & 0xC0) == 0x80) {
		if (utf8[0] == 0xFC && (utf8[1] & 0xFC) == 0x80) /* overlong sequence check */
			return 0;
		return 6;
	}
	else {
		return 0;
	}
}