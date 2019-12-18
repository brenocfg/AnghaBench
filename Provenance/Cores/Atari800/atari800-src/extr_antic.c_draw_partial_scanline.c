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
typedef  int /*<<< orphan*/  UWORD ;
typedef  int /*<<< orphan*/  ULONG ;

/* Variables and functions */
 int ANTIC_DMACTL ; 
 scalar_t__ ANTIC_margin ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/ * GTIA_pm_scanline ; 
 int LCHOP ; 
 size_t NORMAL1 ; 
 size_t NORMAL2 ; 
 int RCHOP ; 
 size_t SCROLL1 ; 
 size_t SCROLL2 ; 
 int /*<<< orphan*/  antic_load () ; 
 scalar_t__ antic_memory ; 
 int anticmode ; 
 scalar_t__* ch_offset ; 
 int* chars_displayed ; 
 int /*<<< orphan*/  draw_antic_0_ptr () ; 
 int /*<<< orphan*/  draw_antic_ptr (int,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int left_border_chars ; 
 int left_border_start ; 
 size_t md ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ need_load ; 
 int right_border_end ; 
 int right_border_start ; 
 int scanlines_to_curses_display ; 
 int /*<<< orphan*/ * scrn_ptr ; 
 int* x_min ; 

void draw_partial_scanline(int l, int r)
{
	/* lborder_chars: save left border chars,we restore it after */
	/*                it is the number of 8pixel 'chars' in the left border */
	int lborder_chars = left_border_chars;

	/* rborder_start: save right border start, we restore it after */
	/*                it is the start of the right border, in words */
	int rborder_start = right_border_start;

	/* lborder_start: start of the left border, in words */
	int lborder_start = LCHOP * 4;
	/* end of the left border, in words */
	int lborder_end = LCHOP * 4 + left_border_chars * 4;
	/* end of the right border, in words */
	int rborder_end = (48 - RCHOP) * 4;
	/* flag: if true, don't show playfield. used if the partial scanline */
	/*    does not include the playfield */
	int dont_display_playfield = 0;
	/* offset of the left most drawable 8 pixel pf block */
	/* int l_pfchar = (lborder_end - x_min[md]) / 4; */
	int l_pfchar = 0;
	/* offset of the right most drawable 8 pixel pf plock, *plus one* */
	int r_pfchar = 0;
	/* buffer to save 0,1,2 or 3 words of the left hand portion of an 8pixel */
	/* 'char' which is going to be erased by the left hand side of the */
	/* left most 8pixel 'char' in the partial scanline and must be saved */
	/* and restored later */
	UWORD sv_buf[4];
	/* buffer to save 0 or 1 (modes 6,7,a,b,c) ,or , (0,1,2 or 3) (modes 8,9) */
	/* 8pixel 'chars' of playfield which is going to be erased by the left */
	/* hand most 8pixel 'char's of the 2(modes 67abc) or 4(modes 89) 8pixel */
	/* 'char'-sized blocks that these modes must draw. */
	UWORD sv_buf2[4 * 4]; /* for modes 6,7,8,9,a,b,c */
	/* start,size of the above buffers */
	int sv_bufstart = 0;
	int sv_bufsize = 0;
	int sv_bufstart2 = 0;
	int sv_bufsize2 = 0;
	/* number of 8,16,32pixel chars to draw in the playfield */
	int nchars = 0;
	/* adjustment to ch_index , it is the number of 8,16,32pixel chars */
	/* that we do not draw on the left hand side that would usually be drawn */
	/* for this mode */
	int ch_adj = 0;
	/* adjustment to x_min to skip over the left side */
	int x_min_adj = 0;
	/* it's the offset of the left most drawable 8pixel pfblock which is */
	/* rounded *down* to the nearest factor of (2:mode 67abc,4:mode 89) */
	/* if it is divided by (2:mode 67abc,4:mode 89) it will give the */
	/* offset of the left most drawable (16,32)pixel 'char' */
	int l_pfactual = 0;
	/* it is the offset of the right most drawable 8pixel pf block which is */
	/* rounded *up* to the nearest factor of (2,4),  *plus one* */
	/* so that r_pfactual-l_pfactual / (2,4) = number of 16,32 pixel 'chars' */
	/* to be drawn */
	int r_pfactual = 0;
	/* it is the offset of the 8pixel block aligned with pf which overlaps */
	/* the left border. We need this for modes 6-c, because in these modes */
	/* the code will save 8pixel blocks to the left of l_pfchar and */
	/* >= l_pfactual, which will result in portions of the left border */
	/* being saved on some occasions which should not be, unless we */
	/* use this variable to alter the number of chars saved */
	/* int l_borderpfchar=0; */

	r_pfchar = chars_displayed[md];
	if (md == NORMAL1 || md == SCROLL1) { /* modes 6,7,a,b,c */
		r_pfchar *= 2;
	}
	else if (md == NORMAL2 || md == SCROLL2) { /* modes 8,9 */
		r_pfchar *= 4;
	}
	if (anticmode < 2 || (ANTIC_DMACTL & 3) == 0) {
		lborder_end = rborder_end;
		dont_display_playfield = 1;
	}
	if (l > rborder_end)
		l = rborder_end;
	if (r > rborder_end)
		r = rborder_end;
	if (l < lborder_start)
		l = lborder_start;
	if (r < lborder_start)
		r = lborder_start;
	if (l >= r)
		return;
	if (l < lborder_end) {
		/* left point is within left border */
		sv_bufstart = (l & (~3)); /* high order bits give buffer start */
		sv_bufsize = l - sv_bufstart;
		left_border_start = sv_bufstart;
		left_border_chars = lborder_chars - (sv_bufstart - lborder_start) / 4;
		if (l > x_min[md]) {
			/* special case for modes 56789abc */
			/* position buffer within the reference frame */
			/* of the playfield if that */
			/* results in more pixels being saved in the buffer */
			/* needed because for modes 5789abc the overlapping part */
			/* can be more than 1 8pixel char and we only save the left */
			/* hand most 8pixel chars in the code in the later section */
			/* further down, so there is a possibility that the 8pixels */
			/* which are saved within the reference frame of the border */
			/* are not enough to ensure that everything gets saved */
			l_pfchar = (l - x_min[md]) / 4;
			if (((l - x_min[md]) & 3) > sv_bufsize) {
				sv_bufsize = ((l - x_min[md]) & 3);
				sv_bufstart = l - sv_bufsize;
			}
		}
	}
	else if (l >= rborder_start) {
		sv_bufstart = (l & (~3)); /* high order bits give buffer start */
		sv_bufsize = l - sv_bufstart;
		right_border_start = sv_bufstart;
		dont_display_playfield = 1; /* don't display the playfield */
	}
	else { /*within screen */
		sv_bufsize = ((l - x_min[md]) & 3); /* low bits have buf size */
		sv_bufstart = l - sv_bufsize; /* difference gives start */
		l_pfchar = (sv_bufstart - x_min[md]) / 4;
		left_border_chars = 0; /* don't display left border */
	}
	memcpy(sv_buf, scrn_ptr + sv_bufstart, sv_bufsize * sizeof(UWORD)); /* save part of screen */

	if (r <= lborder_end) {
		/* right_end_char = (r + 3) / 4; */
		left_border_chars = (r + 3) / 4 - sv_bufstart / 4;
		/* everything must be within the left border */
		dont_display_playfield = 1; /* don't display the playfield */
	}
	else { /* right point is past start of playfield */
		/* now load ANTIC data: needed for ANTIC glitches */
		if (need_load) {
			antic_load();
#ifdef USE_CURSES
			/* Normally, we would call curses_display_line here,
			   and not use scanlines_to_curses_display at all.
			   That would however cause incorrect color of the "MEMORY"
			   menu item in Self Test - it isn't set properly
			   in the first scanline. We therefore postpone
			   curses_display_line call to the next scanline. */
			scanlines_to_curses_display = 1;
#endif
			need_load = FALSE;
		}

		if (r > rborder_start) {
			right_border_end = ((r + 3) & (~3)); /* round up to nearest 8pixel */
		}
		else {
			r_pfchar = (r - x_min[md] + 3) / 4; /* round up to nearest 8pixel */
		}
	}
	if (dont_display_playfield) {
		nchars = 0;
		x_min_adj = 0;
		ch_adj = 0;
	}
	else if (md == NORMAL1 || md == SCROLL1) { /* modes 6,7,a,b,c */
		l_pfactual = (l_pfchar & (~1)); /* round down to nearest 16pixel */
		sv_bufsize2 = (l_pfchar - l_pfactual) * 4;
		sv_bufstart2 = x_min[md] + l_pfactual * 4;
		r_pfactual = ((r_pfchar + 1) & (~1)); /* round up to nearest 16pixel */
		nchars = (r_pfactual - l_pfactual) / 2;
		x_min_adj = l_pfactual * 4;
		ch_adj = l_pfactual / 2;
	}
	else if (md == NORMAL2 || md == SCROLL2) { /* modes 8,9 */
		l_pfactual = (l_pfchar & (~3));
		sv_bufsize2 = (l_pfchar - l_pfactual) * 4;
		sv_bufstart2 = x_min[md] + l_pfactual * 4;
		r_pfactual = ((r_pfchar + 3) & (~3));
		nchars = (r_pfactual - l_pfactual) / 4;
		x_min_adj = l_pfactual * 4;
		ch_adj = l_pfactual / 4;
	}
	else {
		nchars = r_pfchar - l_pfchar;
		x_min_adj = l_pfchar * 4;
		ch_adj = l_pfchar;
	}
	memcpy(sv_buf2, scrn_ptr + sv_bufstart2, sv_bufsize2 * sizeof(UWORD)); /* save part of screen */

	if (dont_display_playfield) {
/* the idea here is to use draw_antic_0_ptr() to draw just the border only, since */
/* we can't set nchars=0.  draw_antic_0_ptr will work if left_border_start and */
/* right_border_end are set correctly */
		if (anticmode < 2 || (ANTIC_DMACTL & 3) == 0 || r <= lborder_end) {
			right_border_end = left_border_start + left_border_chars * 4;
		}
		else if (l >= rborder_start) {
			left_border_start = right_border_start;
		}
		draw_antic_0_ptr();
	}
	else {
		draw_antic_ptr(nchars, /* chars_displayed[md], */
			antic_memory + ANTIC_margin + ch_offset[md] + ch_adj,
			scrn_ptr + x_min[md] + x_min_adj,
			(ULONG *) &GTIA_pm_scanline[x_min[md] + x_min_adj]);
	}
	memcpy(scrn_ptr + sv_bufstart2, sv_buf2, sv_bufsize2 * sizeof(UWORD)); /* restore screen */
	memcpy(scrn_ptr + sv_bufstart, sv_buf, sv_bufsize * sizeof(UWORD)); /* restore screen */

	/* restore border global variables */
	left_border_chars=lborder_chars;
	right_border_start=rborder_start;
	left_border_start = LCHOP * 4;
	right_border_end = (48-RCHOP)  *4;
}