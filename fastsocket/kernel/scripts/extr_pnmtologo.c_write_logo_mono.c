#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ red; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  is_black (TYPE_1__) ; 
 int /*<<< orphan*/  is_white (TYPE_1__) ; 
 TYPE_1__** logo_data ; 
 unsigned int logo_height ; 
 unsigned int logo_width ; 
 int /*<<< orphan*/  write_footer () ; 
 int /*<<< orphan*/  write_header () ; 
 int /*<<< orphan*/  write_hex (unsigned char) ; 

__attribute__((used)) static void write_logo_mono(void)
{
    unsigned int i, j;
    unsigned char val, bit;

    /* validate image */
    for (i = 0; i < logo_height; i++)
	for (j = 0; j < logo_width; j++)
	    if (!is_black(logo_data[i][j]) && !is_white(logo_data[i][j]))
		die("Image must be monochrome\n");

    /* write file header */
    write_header();

    /* write logo data */
    for (i = 0; i < logo_height; i++) {
	for (j = 0; j < logo_width;) {
	    for (val = 0, bit = 0x80; bit && j < logo_width; j++, bit >>= 1)
		if (logo_data[i][j].red)
		    val |= bit;
	    write_hex(val);
	}
    }

    /* write logo structure and file footer */
    write_footer();
}