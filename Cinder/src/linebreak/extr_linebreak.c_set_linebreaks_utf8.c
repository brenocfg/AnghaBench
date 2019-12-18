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
typedef  int /*<<< orphan*/  utf8_t ;
typedef  int /*<<< orphan*/  get_next_char_t ;

/* Variables and functions */
 scalar_t__ lb_get_next_char_utf8 ; 
 int /*<<< orphan*/  set_linebreaks (int /*<<< orphan*/  const*,size_t,char const*,char*,int /*<<< orphan*/ ) ; 

void set_linebreaks_utf8(
		const utf8_t *s,
		size_t len,
		const char *lang,
		char *brks)
{
	set_linebreaks(s, len, lang, brks,
				   (get_next_char_t)lb_get_next_char_utf8);
}