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
struct TYPE_3__ {int loaded; unsigned char* palette; int /*<<< orphan*/  filename; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ COLOURS_EXTERNAL_t ;

/* Variables and functions */
 int EOF ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 

int COLOURS_EXTERNAL_Read(COLOURS_EXTERNAL_t *colours)
{
	FILE *fp;
	int i;
	unsigned char *pal_ptr;

	fp = fopen(colours->filename, "rb");
	if (fp == NULL) {
		colours->loaded = FALSE;
		return FALSE;
	}
	for (i = 0, pal_ptr = colours->palette; i < 768; i++) {
		int c = fgetc(fp);
		if (c == EOF) {
			fclose(fp);
			colours->loaded = FALSE;
			return FALSE;
		}
		*pal_ptr++ = c;
	}
	fclose(fp);
	colours->loaded = TRUE;
	return TRUE;
}