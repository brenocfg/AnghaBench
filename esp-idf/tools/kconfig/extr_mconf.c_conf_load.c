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
#define  KEY_ESC 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  conf_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dialog_clear () ; 
 int /*<<< orphan*/ * dialog_input_result ; 
 int dialog_inputbox (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  load_config_help ; 
 int /*<<< orphan*/  load_config_text ; 
 int /*<<< orphan*/  set_config_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_helptext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_textbox (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sym_set_change_count (int) ; 

__attribute__((used)) static void conf_load(void)
{

	while (1) {
		int res;
		dialog_clear();
		res = dialog_inputbox(NULL, load_config_text,
				      11, 55, filename);
		switch(res) {
		case 0:
			if (!dialog_input_result[0])
				return;
			if (!conf_read(dialog_input_result)) {
				set_config_filename(dialog_input_result);
				sym_set_change_count(1);
				return;
			}
			show_textbox(NULL, _("File does not exist!"), 5, 38);
			break;
		case 1:
			show_helptext(_("Load Alternate Configuration"), load_config_help);
			break;
		case KEY_ESC:
			return;
		}
	}
}