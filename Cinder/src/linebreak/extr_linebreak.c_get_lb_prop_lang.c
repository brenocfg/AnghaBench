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
struct LineBreakPropertiesLang {struct LineBreakProperties* lbp; int /*<<< orphan*/  namelen; int /*<<< orphan*/ * lang; } ;
struct LineBreakProperties {int dummy; } ;

/* Variables and functions */
 struct LineBreakPropertiesLang* lb_prop_lang_map ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct LineBreakProperties *get_lb_prop_lang(const char *lang)
{
	struct LineBreakPropertiesLang *lbplIter;
	if (lang != NULL)
	{
		for (lbplIter = lb_prop_lang_map; lbplIter->lang != NULL; ++lbplIter)
		{
			if (strncmp(lang, lbplIter->lang, lbplIter->namelen) == 0)
			{
				return lbplIter->lbp;
			}
		}
	}
	return NULL;
}