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
typedef  enum LineBreakClass { ____Placeholder_LineBreakClass } LineBreakClass ;

/* Variables and functions */
#define  LBP_AI 131 
 int LBP_AL ; 
 int LBP_ID ; 
#define  LBP_SA 130 
#define  LBP_SG 129 
#define  LBP_XX 128 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static enum LineBreakClass resolve_lb_class(
		enum LineBreakClass lbc,
		const char *lang)
{
	switch (lbc)
	{
	case LBP_AI:
		if (lang != NULL &&
				(strncmp(lang, "zh", 2) == 0 ||	/* Chinese */
				 strncmp(lang, "ja", 2) == 0 ||	/* Japanese */
				 strncmp(lang, "ko", 2) == 0))	/* Korean */
		{
			return LBP_ID;
		}
		/* Fall through */
	case LBP_SA:
	case LBP_SG:
	case LBP_XX:
		return LBP_AL;
	default:
		return lbc;
	}
}