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
typedef  int v4l2_std_id ;
typedef  int u64 ;
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct cx18_av_state {int std; int slicer_line_delay; int slicer_line_offset; struct v4l2_subdev sd; } ;
struct cx18 {struct cx18_av_state av_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_DEBUG_INFO_DEV (struct v4l2_subdev*,char*,int const,int const,...) ; 
 int V4L2_STD_625_50 ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_PAL ; 
 int V4L2_STD_PAL_60 ; 
 int V4L2_STD_PAL_M ; 
 int V4L2_STD_PAL_Nc ; 
 int cx18_av_read (struct cx18*,int) ; 
 int cx18_av_read4 (struct cx18*,int) ; 
 int /*<<< orphan*/  cx18_av_write (struct cx18*,int,int) ; 
 int /*<<< orphan*/  do_div (int,int const) ; 

void cx18_av_std_setup(struct cx18 *cx)
{
	struct cx18_av_state *state = &cx->av_state;
	struct v4l2_subdev *sd = &state->sd;
	v4l2_std_id std = state->std;

	/*
	 * Video ADC crystal clock to pixel clock SRC decimation ratio
	 * 28.636360 MHz/13.5 Mpps * 256 = 0x21f.07b
	 */
	const int src_decimation = 0x21f;

	int hblank, hactive, burst, vblank, vactive, sc;
	int vblank656;
	int luma_lpf, uv_lpf, comb;
	u32 pll_int, pll_frac, pll_post;

	/* datasheet startup, step 8d */
	if (std & ~V4L2_STD_NTSC)
		cx18_av_write(cx, 0x49f, 0x11);
	else
		cx18_av_write(cx, 0x49f, 0x14);

	/*
	 * Note: At the end of a field, there are 3 sets of half line duration
	 * (double horizontal rate) pulses:
	 *
	 * 5 (625) or 6 (525) half-lines to blank for the vertical retrace
	 * 5 (625) or 6 (525) vertical sync pulses of half line duration
	 * 5 (625) or 6 (525) half-lines of equalization pulses
	 */
	if (std & V4L2_STD_625_50) {
		/*
		 * The following relationships of half line counts should hold:
		 * 625 = vblank656 + vactive
		 * 10 = vblank656 - vblank = vsync pulses + equalization pulses
		 *
		 * vblank656: half lines after line 625/mid-313 of blanked video
		 * vblank:    half lines, after line 5/317, of blanked video
		 * vactive:   half lines of active video +
		 * 		5 half lines after the end of active video
		 *
		 * As far as I can tell:
		 * vblank656 starts counting from the falling edge of the first
		 * 	vsync pulse (start of line 1 or mid-313)
		 * vblank starts counting from the after the 5 vsync pulses and
		 * 	5 or 4 equalization pulses (start of line 6 or 318)
		 *
		 * For 625 line systems the driver will extract VBI information
		 * from lines 6-23 and lines 318-335 (but the slicer can only
		 * handle 17 lines, not the 18 in the vblank region).
		 * In addition, we need vblank656 and vblank to be one whole
		 * line longer, to cover line 24 and 336, so the SAV/EAV RP
		 * codes get generated such that the encoder can actually
		 * extract line 23 & 335 (WSS).  We'll lose 1 line in each field
		 * at the top of the screen.
		 *
		 * It appears the 5 half lines that happen after active
		 * video must be included in vactive (579 instead of 574),
		 * otherwise the colors get badly displayed in various regions
		 * of the screen.  I guess the chroma comb filter gets confused
		 * without them (at least when a PVR-350 is the PAL source).
		 */
		vblank656 = 48; /* lines  1 -  24  &  313 - 336 */
		vblank = 38;    /* lines  6 -  24  &  318 - 336 */
		vactive = 579;  /* lines 24 - 313  &  337 - 626 */

		/*
		 * For a 13.5 Mpps clock and 15,625 Hz line rate, a line is
		 * is 864 pixels = 720 active + 144 blanking.  ITU-R BT.601
		 * specifies 12 luma clock periods or ~ 0.9 * 13.5 Mpps after
		 * the end of active video to start a horizontal line, so that
		 * leaves 132 pixels of hblank to ignore.
		 */
		hblank = 132;
		hactive = 720;

		/*
		 * Burst gate delay (for 625 line systems)
		 * Hsync leading edge to color burst rise = 5.6 us
		 * Color burst width = 2.25 us
		 * Gate width = 4 pixel clocks
		 * (5.6 us + 2.25/2 us) * 13.5 Mpps + 4/2 clocks = 92.79 clocks
		 */
		burst = 93;
		luma_lpf = 2;
		if (std & V4L2_STD_PAL) {
			uv_lpf = 1;
			comb = 0x20;
			/* sc = 4433618.75 * src_decimation/28636360 * 2^13 */
			sc = 688700;
		} else if (std == V4L2_STD_PAL_Nc) {
			uv_lpf = 1;
			comb = 0x20;
			/* sc = 3582056.25 * src_decimation/28636360 * 2^13 */
			sc = 556422;
		} else { /* SECAM */
			uv_lpf = 0;
			comb = 0;
			/* (fr + fb)/2 = (4406260 + 4250000)/2 = 4328130 */
			/* sc = 4328130 * src_decimation/28636360 * 2^13 */
			sc = 672314;
		}
	} else {
		/*
		 * The following relationships of half line counts should hold:
		 * 525 = prevsync + vblank656 + vactive
		 * 12 = vblank656 - vblank = vsync pulses + equalization pulses
		 *
		 * prevsync:  6 half-lines before the vsync pulses
		 * vblank656: half lines, after line 3/mid-266, of blanked video
		 * vblank:    half lines, after line 9/272, of blanked video
		 * vactive:   half lines of active video
		 *
		 * As far as I can tell:
		 * vblank656 starts counting from the falling edge of the first
		 * 	vsync pulse (start of line 4 or mid-266)
		 * vblank starts counting from the after the 6 vsync pulses and
		 * 	6 or 5 equalization pulses (start of line 10 or 272)
		 *
		 * For 525 line systems the driver will extract VBI information
		 * from lines 10-21 and lines 273-284.
		 */
		vblank656 = 38; /* lines  4 -  22  &  266 - 284 */
		vblank = 26;	/* lines 10 -  22  &  272 - 284 */
		vactive = 481;  /* lines 23 - 263  &  285 - 525 */

		/*
		 * For a 13.5 Mpps clock and 15,734.26 Hz line rate, a line is
		 * is 858 pixels = 720 active + 138 blanking.  The Hsync leading
		 * edge should happen 1.2 us * 13.5 Mpps ~= 16 pixels after the
		 * end of active video, leaving 122 pixels of hblank to ignore
		 * before active video starts.
		 */
		hactive = 720;
		hblank = 122;
		luma_lpf = 1;
		uv_lpf = 1;

		/*
		 * Burst gate delay (for 525 line systems)
		 * Hsync leading edge to color burst rise = 5.3 us
		 * Color burst width = 2.5 us
		 * Gate width = 4 pixel clocks
		 * (5.3 us + 2.5/2 us) * 13.5 Mpps + 4/2 clocks = 90.425 clocks
		 */
		if (std == V4L2_STD_PAL_60) {
			burst = 90;
			luma_lpf = 2;
			comb = 0x20;
			/* sc = 4433618.75 * src_decimation/28636360 * 2^13 */
			sc = 688700;
		} else if (std == V4L2_STD_PAL_M) {
			/* The 97 needs to be verified against PAL-M timings */
			burst = 97;
			comb = 0x20;
			/* sc = 3575611.49 * src_decimation/28636360 * 2^13 */
			sc = 555421;
		} else {
			burst = 90;
			comb = 0x66;
			/* sc = 3579545.45.. * src_decimation/28636360 * 2^13 */
			sc = 556032;
		}
	}

	/* DEBUG: Displays configured PLL frequency */
	pll_int = cx18_av_read(cx, 0x108);
	pll_frac = cx18_av_read4(cx, 0x10c) & 0x1ffffff;
	pll_post = cx18_av_read(cx, 0x109);
	CX18_DEBUG_INFO_DEV(sd, "PLL regs = int: %u, frac: %u, post: %u\n",
			    pll_int, pll_frac, pll_post);

	if (pll_post) {
		int fsc, pll;
		u64 tmp;

		pll = (28636360L * ((((u64)pll_int) << 25) + pll_frac)) >> 25;
		pll /= pll_post;
		CX18_DEBUG_INFO_DEV(sd, "Video PLL = %d.%06d MHz\n",
				    pll / 1000000, pll % 1000000);
		CX18_DEBUG_INFO_DEV(sd, "Pixel rate = %d.%06d Mpixel/sec\n",
				    pll / 8000000, (pll / 8) % 1000000);

		CX18_DEBUG_INFO_DEV(sd, "ADC XTAL/pixel clock decimation ratio "
				    "= %d.%03d\n", src_decimation / 256,
				    ((src_decimation % 256) * 1000) / 256);

		tmp = 28636360 * (u64) sc;
		do_div(tmp, src_decimation);
		fsc = tmp >> 13;
		CX18_DEBUG_INFO_DEV(sd,
				    "Chroma sub-carrier initial freq = %d.%06d "
				    "MHz\n", fsc / 1000000, fsc % 1000000);

		CX18_DEBUG_INFO_DEV(sd, "hblank %i, hactive %i, vblank %i, "
				    "vactive %i, vblank656 %i, src_dec %i, "
				    "burst 0x%02x, luma_lpf %i, uv_lpf %i, "
				    "comb 0x%02x, sc 0x%06x\n",
				    hblank, hactive, vblank, vactive, vblank656,
				    src_decimation, burst, luma_lpf, uv_lpf,
				    comb, sc);
	}

	/* Sets horizontal blanking delay and active lines */
	cx18_av_write(cx, 0x470, hblank);
	cx18_av_write(cx, 0x471, 0xff & (((hblank >> 8) & 0x3) |
						(hactive << 4)));
	cx18_av_write(cx, 0x472, hactive >> 4);

	/* Sets burst gate delay */
	cx18_av_write(cx, 0x473, burst);

	/* Sets vertical blanking delay and active duration */
	cx18_av_write(cx, 0x474, vblank);
	cx18_av_write(cx, 0x475, 0xff & (((vblank >> 8) & 0x3) |
						(vactive << 4)));
	cx18_av_write(cx, 0x476, vactive >> 4);
	cx18_av_write(cx, 0x477, vblank656);

	/* Sets src decimation rate */
	cx18_av_write(cx, 0x478, 0xff & src_decimation);
	cx18_av_write(cx, 0x479, 0xff & (src_decimation >> 8));

	/* Sets Luma and UV Low pass filters */
	cx18_av_write(cx, 0x47a, luma_lpf << 6 | ((uv_lpf << 4) & 0x30));

	/* Enables comb filters */
	cx18_av_write(cx, 0x47b, comb);

	/* Sets SC Step*/
	cx18_av_write(cx, 0x47c, sc);
	cx18_av_write(cx, 0x47d, 0xff & sc >> 8);
	cx18_av_write(cx, 0x47e, 0xff & sc >> 16);

	if (std & V4L2_STD_625_50) {
		state->slicer_line_delay = 1;
		state->slicer_line_offset = (6 + state->slicer_line_delay - 2);
	} else {
		state->slicer_line_delay = 0;
		state->slicer_line_offset = (10 + state->slicer_line_delay - 2);
	}
	cx18_av_write(cx, 0x47f, state->slicer_line_delay);
}