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

/* Variables and functions */
 int /*<<< orphan*/ * clut_vga16 ; 
 int /*<<< orphan*/  die (char*) ; 
 scalar_t__ is_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** logo_data ; 
 unsigned int logo_height ; 
 unsigned int logo_width ; 
 int /*<<< orphan*/  write_footer () ; 
 int /*<<< orphan*/  write_header () ; 
 int /*<<< orphan*/  write_hex (unsigned char) ; 

__attribute__((used)) static void write_logo_vga16(void)
{
    unsigned int i, j, k;
    unsigned char val;

    /* validate image */
    for (i = 0; i < logo_height; i++)
	for (j = 0; j < logo_width; j++) {
	    for (k = 0; k < 16; k++)
		if (is_equal(logo_data[i][j], clut_vga16[k]))
		    break;
	    if (k == 16)
		die("Image must use the 16 console colors only\n"
		    "Use ppmquant(1) -map clut_vga16.ppm to reduce the number "
		    "of colors\n");
	}

    /* write file header */
    write_header();

    /* write logo data */
    for (i = 0; i < logo_height; i++)
	for (j = 0; j < logo_width; j++) {
	    for (k = 0; k < 16; k++)
		if (is_equal(logo_data[i][j], clut_vga16[k]))
		    break;
	    val = k<<4;
	    if (++j < logo_width) {
		for (k = 0; k < 16; k++)
		    if (is_equal(logo_data[i][j], clut_vga16[k]))
			break;
		val |= k;
	    }
	    write_hex(val);
	}

    /* write logo structure and file footer */
    write_footer();
}