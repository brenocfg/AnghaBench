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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  UBYTE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ANTIC_Frame (int) ; 
 int ATARI_LEFT_MARGIN ; 
 int FALSE ; 
 int Screen_HEIGHT ; 
 int /*<<< orphan*/  Screen_SavePCX (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Screen_SavePNG (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int Screen_WIDTH ; 
 int /*<<< orphan*/ * Screen_atari ; 
 int TRUE ; 
 scalar_t__ Util_malloc (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ striendswith (char const*,char*) ; 

int Screen_SaveScreenshot(const char *filename, int interlaced)
{
	int is_png;
	FILE *fp;
	ULONG *main_screen_atari;
	UBYTE *ptr1;
	UBYTE *ptr2;
	if (striendswith(filename, ".pcx"))
		is_png = 0;
#ifdef HAVE_LIBPNG
	else if (striendswith(filename, ".png"))
		is_png = 1;
#endif
	else
		return FALSE;
	fp = fopen(filename, "wb");
	if (fp == NULL)
		return FALSE;
	main_screen_atari = Screen_atari;
	ptr1 = (UBYTE *) Screen_atari + ATARI_LEFT_MARGIN;
	if (interlaced) {
		Screen_atari = (ULONG *) Util_malloc(Screen_WIDTH * Screen_HEIGHT);
		ptr2 = (UBYTE *) Screen_atari + ATARI_LEFT_MARGIN;
		ANTIC_Frame(TRUE); /* draw on Screen_atari */
	}
	else {
		ptr2 = NULL;
	}
#ifdef HAVE_LIBPNG
	if (is_png)
		Screen_SavePNG(fp, ptr1, ptr2);
	else
#endif
		Screen_SavePCX(fp, ptr1, ptr2);
	fclose(fp);
	if (interlaced) {
		free(Screen_atari);
		Screen_atari = main_screen_atari;
	}
	return TRUE;
}