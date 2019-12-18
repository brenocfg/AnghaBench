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
typedef  int /*<<< orphan*/  spl_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 short ISO_CHAR_HEIGHT ; 
 int ISO_CHAR_MAX ; 
 int ISO_CHAR_MIN ; 
 short ISO_CHAR_WIDTH ; 
 int /*<<< orphan*/  VCPUTC_LOCK_LOCK () ; 
 int /*<<< orphan*/  VCPUTC_LOCK_UNLOCK () ; 
 scalar_t__ kalloc (unsigned int) ; 
 int /*<<< orphan*/  kfree (unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  splhigh () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_render_char (int,unsigned char*,short) ; 
 int vc_rendered_char_size ; 
 unsigned char* vc_rendered_font ; 
 unsigned int vc_rendered_font_size ; 
 scalar_t__ vm_initialized ; 

__attribute__((used)) static void
vc_render_font(short newdepth)
{
	static short olddepth = 0;

	int charindex;	/* index in ISO font */
	unsigned char *rendered_font;
	unsigned int rendered_font_size;
	int rendered_char_size;
	spl_t s;

	if (vm_initialized == FALSE) {
		return;	/* nothing to do */
	}
	if (olddepth == newdepth && vc_rendered_font) {
		return;	/* nothing to do */
	}

	s = splhigh();
	VCPUTC_LOCK_LOCK();

	rendered_font      = vc_rendered_font;
	rendered_font_size = vc_rendered_font_size;
	rendered_char_size = vc_rendered_char_size;

	vc_rendered_font      = NULL;
	vc_rendered_font_size = 0;
	vc_rendered_char_size = 0;

	VCPUTC_LOCK_UNLOCK();
	splx(s);

	if (rendered_font) {
		kfree(rendered_font, rendered_font_size);
		rendered_font = NULL;
	}

	if (newdepth) {
		rendered_char_size = ISO_CHAR_HEIGHT * (((newdepth + 7) / 8) * ISO_CHAR_WIDTH);
		rendered_font_size = (ISO_CHAR_MAX-ISO_CHAR_MIN+1) * rendered_char_size;
		rendered_font = (unsigned char *) kalloc(rendered_font_size);
	}

	if (rendered_font == NULL) {
		return;
	}

	for (charindex = ISO_CHAR_MIN; charindex <= ISO_CHAR_MAX; charindex++) {
		vc_render_char(charindex, rendered_font + (charindex * rendered_char_size), newdepth);
	}

	olddepth = newdepth;

	s = splhigh();
	VCPUTC_LOCK_LOCK();

	vc_rendered_font      = rendered_font;
	vc_rendered_font_size = rendered_font_size;
	vc_rendered_char_size = rendered_char_size;

	VCPUTC_LOCK_UNLOCK();
	splx(s);
}