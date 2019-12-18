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
 int /*<<< orphan*/  SLsmg_draw_box (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SLsmg_gotorc (int,int) ; 
 int /*<<< orphan*/  SLsmg_refresh () ; 
 int /*<<< orphan*/  SLsmg_set_color (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLsmg_write_nstring (char*,int) ; 
 int /*<<< orphan*/  SLsmg_write_string (char*) ; 
 int /*<<< orphan*/  SLsmg_write_wrapped_string (unsigned char*,int,int,int,int,int) ; 
 int SLtt_Screen_Cols ; 
 int SLtt_Screen_Rows ; 
 char* strchr (char const*,char) ; 
 int ui__getch (int) ; 

int ui__question_window(const char *title, const char *text,
			const char *exit_msg, int delay_secs)
{
	int x, y;
	int max_len = 0, nr_lines = 0;
	const char *t;

	t = text;
	while (1) {
		const char *sep = strchr(t, '\n');
		int len;

		if (sep == NULL)
			sep = strchr(t, '\0');
		len = sep - t;
		if (max_len < len)
			max_len = len;
		++nr_lines;
		if (*sep == '\0')
			break;
		t = sep + 1;
	}

	max_len += 2;
	nr_lines += 4;
	y = SLtt_Screen_Rows / 2 - nr_lines / 2,
	x = SLtt_Screen_Cols / 2 - max_len / 2;

	SLsmg_set_color(0);
	SLsmg_draw_box(y, x++, nr_lines, max_len);
	if (title) {
		SLsmg_gotorc(y, x + 1);
		SLsmg_write_string((char *)title);
	}
	SLsmg_gotorc(++y, x);
	nr_lines -= 2;
	max_len -= 2;
	SLsmg_write_wrapped_string((unsigned char *)text, y, x,
				   nr_lines, max_len, 1);
	SLsmg_gotorc(y + nr_lines - 2, x);
	SLsmg_write_nstring((char *)" ", max_len);
	SLsmg_gotorc(y + nr_lines - 1, x);
	SLsmg_write_nstring((char *)exit_msg, max_len);
	SLsmg_refresh();
	return ui__getch(delay_secs);
}