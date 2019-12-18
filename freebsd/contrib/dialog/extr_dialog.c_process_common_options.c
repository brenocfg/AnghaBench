#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  eOptions ;
struct TYPE_4__ {int visit_cols; scalar_t__ aspect_ratio; void* no_mouse; void* visit_items; void* tab_len; int /*<<< orphan*/  output; void* use_shadow; void* use_scrollbar; void* separate_str; } ;
struct TYPE_3__ {int defaultno; char* week_start; void* iso_week; void* reorder; void* no_tags; void* no_items; void* begin_x; void* begin_y; void* begin_set; void* ascii_lines; void* no_lines; void* keep_tite; void* time_format; void* date_format; void* help_label; void* exit_label; void* extra_label; void* cancel_label; void* ok_label; void* no_label; void* yes_label; void* dlg_clear_screen; void* trim_whitespace; void* max_input; void* timeout_secs; void* sleep_secs; void* tab_correct; void* column_separator; void* output_separator; void* print_siz; void* last_key; void* keep_window; void* extra_button; void* help_tags; void* help_status; void* help_button; void* help_file; void* help_line; void* item_help; void* insecure; void* default_item; int /*<<< orphan*/  default_button; void* beep_after_signal; void* beep_signal; void* size_err; void* single_quoted; void* quoted; void* nook; void* nocancel; void* cant_kill; void* nocollapse; void* no_nl_expand; void* cr_wrap; void* colors; void* separate_output; void* backtitle; void* title; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_ASPECT_RATIO ; 
 int /*<<< orphan*/  DLG_EXIT_CANCEL ; 
 int /*<<< orphan*/  DLG_TRACE (char*) ; 
 void* FALSE ; 
 int /*<<< orphan*/  IgnoreNonScreen (char**,int) ; 
 int /*<<< orphan*/  PrintTextOnly (char**,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrintVersion (int /*<<< orphan*/ ) ; 
 int SCOLS ; 
 int SLINES ; 
 void* TRUE ; 
 int /*<<< orphan*/  button_code (void*) ; 
 TYPE_2__ dialog_state ; 
 TYPE_1__ dialog_vars ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 void* ignore_unknown ; 
 int /*<<< orphan*/  lookupOption (char*,int) ; 
 int /*<<< orphan*/  mouse_close () ; 
#define  o_allow_close 211 
#define  o_ascii_lines 210 
#define  o_aspect 209 
#define  o_auto_placement 208 
#define  o_backtitle 207 
#define  o_beep 206 
#define  o_beep_after 205 
#define  o_begin 204 
#define  o_cancel_label 203 
#define  o_clear 202 
#define  o_colors 201 
#define  o_column_separator 200 
#define  o_cr_wrap 199 
#define  o_date_format 198 
#define  o_default_button 197 
#define  o_default_item 196 
#define  o_defaultno 195 
#define  o_exit_label 194 
#define  o_extra_button 193 
#define  o_extra_label 192 
#define  o_fixed_font 191 
#define  o_fullbutton 190 
#define  o_help_button 189 
#define  o_help_file 188 
#define  o_help_label 187 
#define  o_help_line 186 
#define  o_help_status 185 
#define  o_help_tags 184 
#define  o_icon 183 
#define  o_ignore 182 
#define  o_insecure 181 
#define  o_iso_week 180 
#define  o_item_help 179 
#define  o_keep_colors 178 
#define  o_keep_tite 177 
#define  o_keep_window 176 
#define  o_last_key 175 
#define  o_max_input 174 
#define  o_no_close 173 
#define  o_no_collapse 172 
#define  o_no_cr_wrap 171 
#define  o_no_items 170 
#define  o_no_kill 169 
#define  o_no_label 168 
#define  o_no_lines 167 
#define  o_no_mouse 166 
#define  o_no_nl_expand 165 
#define  o_no_shadow 164 
#define  o_no_tags 163 
#define  o_nocancel 162 
#define  o_nook 161 
#define  o_ok_label 160 
#define  o_output_separator 159 
#define  o_print_maxsize 158 
#define  o_print_size 157 
#define  o_print_text_only 156 
#define  o_print_text_size 155 
#define  o_print_version 154 
#define  o_quoted 153 
#define  o_reorder 152 
#define  o_screen_center 151 
#define  o_scrollbar 150 
#define  o_separate_output 149 
#define  o_separate_widget 148 
#define  o_separator 147 
#define  o_shadow 146 
#define  o_single_quoted 145 
#define  o_size_err 144 
#define  o_sleep 143 
#define  o_smooth 142 
#define  o_tab_correct 141 
#define  o_tab_len 140 
#define  o_time_format 139 
#define  o_timeout 138 
#define  o_title 137 
#define  o_topleft 136 
#define  o_trace 135 
#define  o_trim 134 
#define  o_under_mouse 133 
#define  o_unknown 132 
#define  o_visit_items 131 
#define  o_week_start 130 
#define  o_wmclass 129 
#define  o_yes_label 128 
 void* optionString (char**,int*) ; 
 void* optionValue (char**,int*) ; 
 int /*<<< orphan*/  process_trace_option (char**,int*) ; 

__attribute__((used)) static int
process_common_options(int argc, char **argv, int offset, bool output)
{
    bool done = FALSE;
    eOptions code;

    DLG_TRACE(("# process_common_options, offset %d\n", offset));

    while (offset < argc && !done) {	/* Common options */
	DLG_TRACE(("#\targv[%d] = %s\n", offset, argv[offset]));
	switch (code = lookupOption(argv[offset], 1)) {
	case o_title:
	    dialog_vars.title = optionString(argv, &offset);
	    break;
	case o_backtitle:
	    dialog_vars.backtitle = optionString(argv, &offset);
	    break;
	case o_separate_widget:
	    dialog_state.separate_str = optionString(argv, &offset);
	    break;
	case o_separate_output:
	    dialog_vars.separate_output = TRUE;
	    break;
	case o_colors:
	    dialog_vars.colors = TRUE;
	    break;
	case o_cr_wrap:
	    dialog_vars.cr_wrap = TRUE;
	    break;
	case o_no_nl_expand:
	    dialog_vars.no_nl_expand = TRUE;
	    break;
	case o_no_collapse:
	    dialog_vars.nocollapse = TRUE;
	    break;
	case o_no_kill:
	    dialog_vars.cant_kill = TRUE;
	    break;
	case o_nocancel:
	    dialog_vars.nocancel = TRUE;
	    break;
	case o_nook:
	    dialog_vars.nook = TRUE;
	    break;
	case o_quoted:
	    dialog_vars.quoted = TRUE;
	    break;
	case o_single_quoted:
	    dialog_vars.single_quoted = TRUE;
	    break;
	case o_size_err:
	    dialog_vars.size_err = TRUE;
	    break;
	case o_beep:
	    dialog_vars.beep_signal = TRUE;
	    break;
	case o_beep_after:
	    dialog_vars.beep_after_signal = TRUE;
	    break;
	case o_scrollbar:
	    dialog_state.use_scrollbar = TRUE;
	    break;
	case o_shadow:
	    dialog_state.use_shadow = TRUE;
	    break;
	case o_defaultno:
	    dialog_vars.defaultno = TRUE;
	    dialog_vars.default_button = DLG_EXIT_CANCEL;
	    break;
	case o_default_button:
	    dialog_vars.default_button = button_code(optionString(argv, &offset));
	    dialog_vars.defaultno = dialog_vars.default_button == DLG_EXIT_CANCEL;
	    break;
	case o_default_item:
	    dialog_vars.default_item = optionString(argv, &offset);
	    break;
	case o_insecure:
	    dialog_vars.insecure = TRUE;
	    break;
	case o_item_help:
	    dialog_vars.item_help = TRUE;
	    break;
	case o_help_line:
	    dialog_vars.help_line = optionString(argv, &offset);
	    break;
	case o_help_file:
	    dialog_vars.help_file = optionString(argv, &offset);
	    break;
	case o_help_button:
	    dialog_vars.help_button = TRUE;
	    break;
	case o_help_status:
	    dialog_vars.help_status = TRUE;
	    break;
	case o_help_tags:
	    dialog_vars.help_tags = TRUE;
	    break;
	case o_extra_button:
	    dialog_vars.extra_button = TRUE;
	    break;
	case o_ignore:
	    ignore_unknown = TRUE;
	    break;
	case o_keep_window:
	    dialog_vars.keep_window = TRUE;
	    break;
	case o_last_key:
	    dialog_vars.last_key = TRUE;
	    break;
	case o_no_shadow:
	    dialog_state.use_shadow = FALSE;
	    break;
	case o_print_size:
	    dialog_vars.print_siz = TRUE;
	    break;
	case o_print_text_only:
	case o_print_text_size:
	    PrintTextOnly(argv, &offset, code);
	    break;
	case o_print_maxsize:
	    if (output) {
		IgnoreNonScreen(argv, offset);
		fflush(dialog_state.output);
		fprintf(dialog_state.output, "MaxSize: %d, %d\n", SLINES, SCOLS);
	    }
	    break;
	case o_print_version:
	    if (output) {
		PrintVersion(dialog_state.output);
	    }
	    break;
	case o_separator:
	case o_output_separator:
	    dialog_vars.output_separator = optionString(argv, &offset);
	    break;
	case o_column_separator:
	    dialog_vars.column_separator = optionString(argv, &offset);
	    break;
	case o_tab_correct:
	    dialog_vars.tab_correct = TRUE;
	    break;
	case o_sleep:
	    dialog_vars.sleep_secs = optionValue(argv, &offset);
	    break;
	case o_timeout:
	    dialog_vars.timeout_secs = optionValue(argv, &offset);
	    break;
	case o_max_input:
	    dialog_vars.max_input = optionValue(argv, &offset);
	    break;
	case o_tab_len:
	    dialog_state.tab_len = optionValue(argv, &offset);
	    break;
	case o_trim:
	    dialog_vars.trim_whitespace = TRUE;
	    break;
	case o_visit_items:
	    dialog_state.visit_items = TRUE;
	    dialog_state.visit_cols = 1;
	    break;
	case o_aspect:
	    dialog_state.aspect_ratio = optionValue(argv, &offset);
	    break;
	case o_begin:
	    dialog_vars.begin_set = TRUE;
	    dialog_vars.begin_y = optionValue(argv, &offset);
	    dialog_vars.begin_x = optionValue(argv, &offset);
	    break;
	case o_clear:
	    dialog_vars.dlg_clear_screen = TRUE;
	    break;
	case o_yes_label:
	    dialog_vars.yes_label = optionString(argv, &offset);
	    break;
	case o_no_label:
	    dialog_vars.no_label = optionString(argv, &offset);
	    break;
	case o_ok_label:
	    dialog_vars.ok_label = optionString(argv, &offset);
	    break;
	case o_cancel_label:
	    dialog_vars.cancel_label = optionString(argv, &offset);
	    break;
	case o_extra_label:
	    dialog_vars.extra_label = optionString(argv, &offset);
	    break;
	case o_exit_label:
	    dialog_vars.exit_label = optionString(argv, &offset);
	    break;
	case o_help_label:
	    dialog_vars.help_label = optionString(argv, &offset);
	    break;
	case o_date_format:
	    dialog_vars.date_format = optionString(argv, &offset);
	    break;
	case o_time_format:
	    dialog_vars.time_format = optionString(argv, &offset);
	    break;
	case o_keep_tite:
	    dialog_vars.keep_tite = TRUE;
	    break;
	case o_ascii_lines:
	    dialog_vars.ascii_lines = TRUE;
	    dialog_vars.no_lines = FALSE;
	    break;
	case o_no_lines:
	    dialog_vars.no_lines = TRUE;
	    dialog_vars.ascii_lines = FALSE;
	    break;
	case o_no_mouse:
	    dialog_state.no_mouse = TRUE;
	    mouse_close();
	    break;
#ifdef HAVE_WHIPTAIL
	case o_topleft:
	    dialog_vars.begin_set = TRUE;
	    dialog_vars.begin_y = 0;
	    dialog_vars.begin_x = 0;
	    break;
	case o_fullbutton:
	    /* ignore */
	    break;
#endif
	    /* options of Xdialog which we ignore */
	case o_icon:
	case o_wmclass:
	    (void) optionString(argv, &offset);
	    /* FALLTHRU */
	case o_allow_close:
	case o_auto_placement:
	case o_fixed_font:
	case o_keep_colors:
	case o_no_close:
	case o_no_cr_wrap:
	case o_screen_center:
	case o_smooth:
	case o_under_mouse:
	    break;
	case o_unknown:
	    if (ignore_unknown)
		break;
	    /* FALLTHRU */
	default:		/* no more common options */
	    done = TRUE;
	    break;
#ifdef HAVE_DLG_TRACE
	case o_trace:
	    process_trace_option(argv, &offset);
	    break;
#endif
#if defined(HAVE_XDIALOG2) || defined(HAVE_WHIPTAIL)
	case o_no_items:
	    dialog_vars.no_items = TRUE;
	    break;
	case o_no_tags:
	    dialog_vars.no_tags = TRUE;
	    break;
#endif
#ifdef HAVE_XDIALOG2
	case o_reorder:
	    dialog_vars.reorder = TRUE;
	    break;
#endif
#ifdef HAVE_XDIALOG
	case o_week_start:
	    dialog_vars.week_start = optionString(argv, &offset);
	    break;
#endif
	case o_iso_week:
	    dialog_vars.iso_week = TRUE;
	    if (dialog_vars.week_start == 0) {	/* Monday is implied */
		static char default_1st[] = "1";
		dialog_vars.week_start = default_1st;
	    }
	    break;
	}
	if (!done)
	    offset++;
    }

    if (dialog_state.aspect_ratio == 0)
	dialog_state.aspect_ratio = DEFAULT_ASPECT_RATIO;

    return offset;
}