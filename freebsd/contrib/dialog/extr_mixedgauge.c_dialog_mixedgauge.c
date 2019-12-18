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
typedef  int /*<<< orphan*/  DIALOG_MIXEDGAUGE ;

/* Variables and functions */
 int /*<<< orphan*/  DLG_EXIT_OK ; 
 int /*<<< orphan*/  DLG_TRACE (char*) ; 
 int /*<<< orphan*/  DLG_TRACE2N (char*,int) ; 
 int /*<<< orphan*/  DLG_TRACE2S (char*,char const*) ; 
 int /*<<< orphan*/  dlg_begin_mixedgauge (int /*<<< orphan*/ *,int*,char const*,char const*,int,int,int,char**) ; 
 int dlg_finish_mixedgauge (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_update_mixedgauge (int /*<<< orphan*/ *,int) ; 

int
dialog_mixedgauge(const char *title,
		  const char *cprompt,
		  int height,
		  int width,
		  int percent,
		  int item_no,
		  char **items)
{
    DIALOG_MIXEDGAUGE dlg;
    int began = 0;

    DLG_TRACE(("# mixedgauge args:\n"));
    DLG_TRACE2S("title", title);
    DLG_TRACE2S("message", cprompt);
    DLG_TRACE2N("height", height);
    DLG_TRACE2N("width", width);
    DLG_TRACE2N("percent", percent);
    DLG_TRACE2N("llength", item_no);
    /* FIXME dump the items[][] too */

    dlg_begin_mixedgauge(&dlg, &began, title, cprompt, height,
			 width, item_no, items);

    dlg_update_mixedgauge(&dlg, percent);

    return dlg_finish_mixedgauge(&dlg, DLG_EXIT_OK);
}