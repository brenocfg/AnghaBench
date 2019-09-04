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
typedef  enum AVLangCodespace { ____Placeholder_AVLangCodespace } AVLangCodespace ;

/* Variables and functions */
 char const* ff_convert_lang_to (char const*,int) ; 

const char *av_convert_lang_to(const char *lang, enum AVLangCodespace target_codespace)
{
    return ff_convert_lang_to(lang, target_codespace);
}