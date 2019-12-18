#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  red; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  is_gray (TYPE_1__) ; 
 TYPE_1__** logo_data ; 
 unsigned int logo_height ; 
 unsigned int logo_width ; 
 int /*<<< orphan*/  write_footer () ; 
 int /*<<< orphan*/  write_header () ; 
 int /*<<< orphan*/  write_hex (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_logo_gray256(void)
{
    unsigned int i, j;

    /* validate image */
    for (i = 0; i < logo_height; i++)
	for (j = 0; j < logo_width; j++)
	    if (!is_gray(logo_data[i][j]))
		die("Image must be grayscale\n");

    /* write file header */
    write_header();

    /* write logo data */
    for (i = 0; i < logo_height; i++)
	for (j = 0; j < logo_width; j++)
	    write_hex(logo_data[i][j].red);

    /* write logo structure and file footer */
    write_footer();
}