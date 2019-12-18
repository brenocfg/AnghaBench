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
 int /*<<< orphan*/  const* lang_for_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lang_lookup_index (char const*) ; 

const iso639_lang_t * lang_lookup( const char * str )
{
    return lang_for_index(lang_lookup_index(str));
}