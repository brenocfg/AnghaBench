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
typedef  int UTF8 ;
typedef  int Boolean ;

/* Variables and functions */

__attribute__((used)) static Boolean isLegalUTF8(const UTF8 *source, int length) {
    UTF8 a;
    const UTF8 *srcptr = source+length;
    switch (length) {
    default: return false;
	/* Everything else falls through when "true"... */
    case 4: if ((a = (*--srcptr)) < 0x80 || a > 0xBF) return false;
    case 3: if ((a = (*--srcptr)) < 0x80 || a > 0xBF) return false;
    case 2: if ((a = (*--srcptr)) > 0xBF) return false;

	switch (*source) {
	    /* no fall-through in this inner switch */
	    case 0xE0: if (a < 0xA0) return false; break;
	    case 0xED: if (a > 0x9F) return false; break;
	    case 0xF0: if (a < 0x90) return false; break;
	    case 0xF4: if (a > 0x8F) return false; break;
	    default:   if (a < 0x80) return false;
	}

    case 1: if (*source >= 0x80 && *source < 0xC2) return false;
    }
    if (*source > 0xF4) return false;
    return true;
}