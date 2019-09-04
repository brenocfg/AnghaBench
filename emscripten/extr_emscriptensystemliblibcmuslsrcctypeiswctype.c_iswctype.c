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
typedef  int /*<<< orphan*/  wint_t ;
typedef  int wctype_t ;

/* Variables and functions */
#define  WCTYPE_ALNUM 139 
#define  WCTYPE_ALPHA 138 
#define  WCTYPE_BLANK 137 
#define  WCTYPE_CNTRL 136 
#define  WCTYPE_DIGIT 135 
#define  WCTYPE_GRAPH 134 
#define  WCTYPE_LOWER 133 
#define  WCTYPE_PRINT 132 
#define  WCTYPE_PUNCT 131 
#define  WCTYPE_SPACE 130 
#define  WCTYPE_UPPER 129 
#define  WCTYPE_XDIGIT 128 
 int iswalnum (int /*<<< orphan*/ ) ; 
 int iswalpha (int /*<<< orphan*/ ) ; 
 int iswblank (int /*<<< orphan*/ ) ; 
 int iswcntrl (int /*<<< orphan*/ ) ; 
 int iswdigit (int /*<<< orphan*/ ) ; 
 int iswgraph (int /*<<< orphan*/ ) ; 
 int iswlower (int /*<<< orphan*/ ) ; 
 int iswprint (int /*<<< orphan*/ ) ; 
 int iswpunct (int /*<<< orphan*/ ) ; 
 int iswspace (int /*<<< orphan*/ ) ; 
 int iswupper (int /*<<< orphan*/ ) ; 
 int iswxdigit (int /*<<< orphan*/ ) ; 

int iswctype(wint_t wc, wctype_t type)
{
	switch (type) {
	case WCTYPE_ALNUM:
		return iswalnum(wc);
	case WCTYPE_ALPHA:
		return iswalpha(wc);
	case WCTYPE_BLANK:
		return iswblank(wc);
	case WCTYPE_CNTRL:
		return iswcntrl(wc);
	case WCTYPE_DIGIT:
		return iswdigit(wc);
	case WCTYPE_GRAPH:
		return iswgraph(wc);
	case WCTYPE_LOWER:
		return iswlower(wc);
	case WCTYPE_PRINT:
		return iswprint(wc);
	case WCTYPE_PUNCT:
		return iswpunct(wc);
	case WCTYPE_SPACE:
		return iswspace(wc);
	case WCTYPE_UPPER:
		return iswupper(wc);
	case WCTYPE_XDIGIT:
		return iswxdigit(wc);
	}
	return 0;
}