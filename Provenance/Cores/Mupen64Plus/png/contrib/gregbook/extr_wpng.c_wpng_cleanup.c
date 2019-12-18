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
struct TYPE_2__ {int /*<<< orphan*/ * row_pointers; int /*<<< orphan*/ * image_data; int /*<<< orphan*/ * infile; int /*<<< orphan*/ * outfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_1__ wpng_info ; 

__attribute__((used)) static void wpng_cleanup(void)
{
    if (wpng_info.outfile) {
        fclose(wpng_info.outfile);
        wpng_info.outfile = NULL;
    }

    if (wpng_info.infile) {
        fclose(wpng_info.infile);
        wpng_info.infile = NULL;
    }

    if (wpng_info.image_data) {
        free(wpng_info.image_data);
        wpng_info.image_data = NULL;
    }

    if (wpng_info.row_pointers) {
        free(wpng_info.row_pointers);
        wpng_info.row_pointers = NULL;
    }
}