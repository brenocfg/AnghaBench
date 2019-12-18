#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* iso639_1; } ;
typedef  TYPE_1__ iso639_lang_t ;

/* Variables and functions */

int lang_to_code(const iso639_lang_t *lang)
{
    int code = 0;

    if (lang)
        code = (lang->iso639_1[0] << 8) | lang->iso639_1[1];

    return code;
}