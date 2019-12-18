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
typedef  int /*<<< orphan*/  iso639_lang_t ;

/* Variables and functions */
 int /*<<< orphan*/  const lang_any ; 
 int lang_count ; 
 int /*<<< orphan*/  const* languages ; 

const iso639_lang_t * lang_for_index( int index )
{
    if (index == -1)
        return &lang_any;

    if (index < 0 || index >= lang_count)
        return NULL;

    return &languages[index];
}