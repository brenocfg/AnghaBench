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
 unsigned int FF_ARRAY_ELEMS (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ ** mov_mdhd_language_map ; 

int ff_mov_lang_to_iso639(unsigned code, char to[4])
{
    int i;
    memset(to, 0, 4);
    /* is it the mangled iso code? */
    /* see http://www.geocities.com/xhelmboyx/quicktime/formats/mp4-layout.txt */
    if (code >= 0x400 && code != 0x7fff) {
        for (i = 2; i >= 0; i--) {
            to[i] = 0x60 + (code & 0x1f);
            code >>= 5;
        }
        return 1;
    }
    /* old fashion apple lang code */
    if (code >= FF_ARRAY_ELEMS(mov_mdhd_language_map))
        return 0;
    if (!mov_mdhd_language_map[code][0])
        return 0;
    memcpy(to, mov_mdhd_language_map[code], 4);
    return 1;
}