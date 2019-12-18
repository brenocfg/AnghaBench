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
typedef  int /*<<< orphan*/  update_text_fn ;

/* Variables and functions */
 int /*<<< orphan*/  dialog_clear () ; 
 int dialog_textbox (char const*,char*,int,int,int*,int*,int*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int show_textbox_ext(const char *title, char *text, int r, int c, int
			    *keys, int *vscroll, int *hscroll, update_text_fn
			    update_text, void *data)
{
	dialog_clear();
	return dialog_textbox(title, text, r, c, keys, vscroll, hscroll,
			      update_text, data);
}