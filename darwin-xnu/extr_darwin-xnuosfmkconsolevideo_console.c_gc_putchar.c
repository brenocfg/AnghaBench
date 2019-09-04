#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ v_columns; scalar_t__ v_rows; } ;

/* Variables and functions */
#define  ESask 136 
#define  EScharsize 135 
#define  ESesc 134 
#define  ESgetpars 133 
#define  ESgotpars 132 
#define  ESnormal 131 
#define  ESsetG0 130 
#define  ESsetG1 129 
#define  ESsquare 128 
 int /*<<< orphan*/  gc_putc_askcmd (char) ; 
 int /*<<< orphan*/  gc_putc_charsetcmd (int,char) ; 
 int /*<<< orphan*/  gc_putc_charsizecmd (char) ; 
 int /*<<< orphan*/  gc_putc_esc (char) ; 
 int /*<<< orphan*/  gc_putc_getpars (char) ; 
 int /*<<< orphan*/  gc_putc_gotpars (char) ; 
 int /*<<< orphan*/  gc_putc_normal (char) ; 
 int /*<<< orphan*/  gc_putc_square (char) ; 
 int gc_vt100state ; 
 scalar_t__ gc_x ; 
 scalar_t__ gc_y ; 
 TYPE_1__ vinfo ; 

__attribute__((used)) static void 
gc_putchar(char ch)
{
	if (!ch) {
		return;	/* ignore null characters */
	}
	switch (gc_vt100state) {
		default:gc_vt100state = ESnormal;	/* FALLTHROUGH */
	case ESnormal:
		gc_putc_normal(ch);
		break;
	case ESesc:
		gc_putc_esc(ch);
		break;
	case ESsquare:
		gc_putc_square(ch);
		break;
	case ESgetpars:
		gc_putc_getpars(ch);
		break;
	case ESgotpars:
		gc_putc_gotpars(ch);
		break;
	case ESask:
		gc_putc_askcmd(ch);
		break;
	case EScharsize:
		gc_putc_charsizecmd(ch);
		break;
	case ESsetG0:
		gc_putc_charsetcmd(0, ch);
		break;
	case ESsetG1:
		gc_putc_charsetcmd(1, ch);
		break;
	}

	if (gc_x >= vinfo.v_columns) {
		if (0 == vinfo.v_columns)
			gc_x = 0;
		else
			gc_x = vinfo.v_columns - 1;
	}
	if (gc_y >= vinfo.v_rows) {
		if (0 == vinfo.v_rows)
			gc_y = 0;
		else
			gc_y = vinfo.v_rows - 1;
	}
}