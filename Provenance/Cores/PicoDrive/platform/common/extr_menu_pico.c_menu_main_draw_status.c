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
typedef  int time_t ;
typedef  int /*<<< orphan*/  time_s ;
struct tm {int dummy; } ;
struct TYPE_2__ {int EmuOpt; } ;

/* Variables and functions */
 int EOPT_SHOW_RTC ; 
 TYPE_1__ currentConfig ; 
 unsigned short* g_screen_ptr ; 
 int g_screen_width ; 
 struct tm* gmtime (int*) ; 
 int me_mfont_h ; 
 int me_mfont_w ; 
 unsigned short menu_text_color ; 
 int plat_target_bat_capacity_get () ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 int /*<<< orphan*/  text_out16 (int,int,char*) ; 
 int time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void menu_main_draw_status(void)
{
	static time_t last_bat_read = 0;
	static int last_bat_val = -1;
	unsigned short *bp = g_screen_ptr;
	int bat_h = me_mfont_h * 2 / 3;
	int i, u, w, wfill, batt_val;
	struct tm *tmp;
	time_t ltime;
	char time_s[16];

	if (!(currentConfig.EmuOpt & EOPT_SHOW_RTC))
		return;

	ltime = time(NULL);
	tmp = gmtime(&ltime);
	strftime(time_s, sizeof(time_s), "%H:%M", tmp);

	text_out16(g_screen_width - me_mfont_w * 6, me_mfont_h + 2, time_s);

	if (ltime - last_bat_read > 10) {
		last_bat_read = ltime;
		last_bat_val = batt_val = plat_target_bat_capacity_get();
	}
	else
		batt_val = last_bat_val;

	if (batt_val < 0 || batt_val > 100)
		return;

	/* battery info */
	bp += (me_mfont_h * 2 + 2) * g_screen_width + g_screen_width - me_mfont_w * 3 - 3;
	for (i = 0; i < me_mfont_w * 2; i++)
		bp[i] = menu_text_color;
	for (i = 0; i < me_mfont_w * 2; i++)
		bp[i + g_screen_width * bat_h] = menu_text_color;
	for (i = 0; i <= bat_h; i++)
		bp[i * g_screen_width] =
		bp[i * g_screen_width + me_mfont_w * 2] = menu_text_color;
	for (i = 2; i < bat_h - 1; i++)
		bp[i * g_screen_width - 1] =
		bp[i * g_screen_width - 2] = menu_text_color;

	w = me_mfont_w * 2 - 1;
	wfill = batt_val * w / 100;
	for (u = 1; u < bat_h; u++)
		for (i = 0; i < wfill; i++)
			bp[(w - i) + g_screen_width * u] = menu_text_color;
}