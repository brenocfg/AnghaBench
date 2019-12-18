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
typedef  int uint8_t ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mov_mdhd_language_map ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

int ff_mov_iso639_to_lang(const char lang[4], int mp4)
{
    int i, code = 0;

    /* old way, only for QT? */
    for (i = 0; lang[0] && !mp4 && i < FF_ARRAY_ELEMS(mov_mdhd_language_map); i++) {
        if (!strcmp(lang, mov_mdhd_language_map[i]))
            return i;
    }
    /* XXX:can we do that in mov too? */
    if (!mp4)
        return -1;
    /* handle undefined as such */
    if (lang[0] == '\0')
        lang = "und";
    /* 5 bits ASCII */
    for (i = 0; i < 3; i++) {
        uint8_t c = lang[i];
        c -= 0x60;
        if (c > 0x1f)
            return -1;
        code <<= 5;
        code |= c;
    }
    return code;
}