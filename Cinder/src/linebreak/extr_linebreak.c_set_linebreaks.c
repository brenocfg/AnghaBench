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
typedef  scalar_t__ utf32_t ;
struct LineBreakProperties {int dummy; } ;
typedef  scalar_t__ (* get_next_char_t ) (void const*,size_t,size_t*) ;
typedef  enum LineBreakClass { ____Placeholder_LineBreakClass } LineBreakClass ;

/* Variables and functions */
#define  CMI_BRK 138 
#define  CMP_BRK 137 
#define  DIR_BRK 136 
 scalar_t__ EOS ; 
#define  IND_BRK 135 
 int LBP_BA ; 
#define  LBP_BK 134 
#define  LBP_CB 133 
#define  LBP_CR 132 
 int LBP_JT ; 
#define  LBP_LF 131 
#define  LBP_NL 130 
#define  LBP_SP 129 
 int LBP_Undefined ; 
 int LBP_WJ ; 
 char LINEBREAK_ALLOWBREAK ; 
 char LINEBREAK_INSIDEACHAR ; 
 char LINEBREAK_MUSTBREAK ; 
 char LINEBREAK_NOBREAK ; 
#define  PRH_BRK 128 
 int /*<<< orphan*/  assert (int) ; 
 int** baTable ; 
 int get_char_lb_class_lang (scalar_t__,struct LineBreakProperties*) ; 
 struct LineBreakProperties* get_lb_prop_lang (char const*) ; 
 int resolve_lb_class (int,char const*) ; 

void set_linebreaks(
		const void *s,
		size_t len,
		const char *lang,
		char *brks,
		get_next_char_t get_next_char)
{
	utf32_t ch;
	enum LineBreakClass lbcCur;
	enum LineBreakClass lbcNew;
	enum LineBreakClass lbcLast;
	struct LineBreakProperties *lbpLang;
	size_t posCur = 0;
	size_t posLast = 0;

	--posLast;	/* To be ++'d later */
	ch = get_next_char(s, len, &posCur);
	if (ch == EOS)
		return;
	lbpLang = get_lb_prop_lang(lang);
	lbcCur = resolve_lb_class(get_char_lb_class_lang(ch, lbpLang), lang);
	lbcNew = LBP_Undefined;

nextline:

	/* Special treatment for the first character */
	switch (lbcCur)
	{
	case LBP_LF:
	case LBP_NL:
		lbcCur = LBP_BK;
		break;
	case LBP_CB:
		lbcCur = LBP_BA;
		break;
	case LBP_SP:
		lbcCur = LBP_WJ;
		break;
	default:
		break;
	}

	/* Process a line till an explicit break or end of string */
	for (;;)
	{
		for (++posLast; posLast < posCur - 1; ++posLast)
		{
			brks[posLast] = LINEBREAK_INSIDEACHAR;
		}
		assert(posLast == posCur - 1);
		lbcLast = lbcNew;
		ch = get_next_char(s, len, &posCur);
		if (ch == EOS)
			break;
		lbcNew = get_char_lb_class_lang(ch, lbpLang);
		if (lbcCur == LBP_BK || (lbcCur == LBP_CR && lbcNew != LBP_LF))
		{
			brks[posLast] = LINEBREAK_MUSTBREAK;
			lbcCur = resolve_lb_class(lbcNew, lang);
			goto nextline;
		}

		switch (lbcNew)
		{
		case LBP_SP:
			brks[posLast] = LINEBREAK_NOBREAK;
			continue;
		case LBP_BK:
		case LBP_LF:
		case LBP_NL:
			brks[posLast] = LINEBREAK_NOBREAK;
			lbcCur = LBP_BK;
			continue;
		case LBP_CR:
			brks[posLast] = LINEBREAK_NOBREAK;
			lbcCur = LBP_CR;
			continue;
		case LBP_CB:
			brks[posLast] = LINEBREAK_ALLOWBREAK;
			lbcCur = LBP_BA;
			continue;
		default:
			break;
		}

		lbcNew = resolve_lb_class(lbcNew, lang);

		assert(lbcCur <= LBP_JT);
		assert(lbcNew <= LBP_JT);
		switch (baTable[lbcCur - 1][lbcNew - 1])
		{
		case DIR_BRK:
			brks[posLast] = LINEBREAK_ALLOWBREAK;
			break;
		case CMI_BRK:
		case IND_BRK:
			if (lbcLast == LBP_SP)
			{
				brks[posLast] = LINEBREAK_ALLOWBREAK;
			}
			else
			{
				brks[posLast] = LINEBREAK_NOBREAK;
			}
			break;
		case CMP_BRK:
			brks[posLast] = LINEBREAK_NOBREAK;
			if (lbcLast != LBP_SP)
				continue;
			break;
		case PRH_BRK:
			brks[posLast] = LINEBREAK_NOBREAK;
			break;
		}

		lbcCur = lbcNew;
	}

	assert(posLast == posCur - 1 && posCur <= len);
	/* Break after the last character */
	brks[posLast] = LINEBREAK_MUSTBREAK;
	/* When the input contains incomplete sequences */
	while (posCur < len)
	{
		brks[posCur++] = LINEBREAK_INSIDEACHAR;
	}
}