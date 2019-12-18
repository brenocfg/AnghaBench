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
struct menu {int dummy; } ;
struct gstr {int dummy; } ;
typedef  int /*<<< orphan*/  GtkTextIter ;
typedef  int /*<<< orphan*/  GtkTextBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TEXT_VIEW (int /*<<< orphan*/ ) ; 
 char* _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_text_buffer_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_text_buffer_get_bounds (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_text_buffer_get_end_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_text_buffer_insert_at_cursor (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  gtk_text_buffer_insert_with_tags (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_text_view_get_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_text_view_set_left_margin (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  menu_get_ext_help (struct menu*,struct gstr*) ; 
 int /*<<< orphan*/  menu_get_prompt (struct menu*) ; 
 int /*<<< orphan*/  str_free (struct gstr*) ; 
 char const* str_get (struct gstr*) ; 
 struct gstr str_new () ; 
 int /*<<< orphan*/  tag1 ; 
 int /*<<< orphan*/  tag2 ; 
 int /*<<< orphan*/  text_w ; 

__attribute__((used)) static void text_insert_help(struct menu *menu)
{
	GtkTextBuffer *buffer;
	GtkTextIter start, end;
	const char *prompt = _(menu_get_prompt(menu));
	struct gstr help = str_new();

	menu_get_ext_help(menu, &help);

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_w));
	gtk_text_buffer_get_bounds(buffer, &start, &end);
	gtk_text_buffer_delete(buffer, &start, &end);
	gtk_text_view_set_left_margin(GTK_TEXT_VIEW(text_w), 15);

	gtk_text_buffer_get_end_iter(buffer, &end);
	gtk_text_buffer_insert_with_tags(buffer, &end, prompt, -1, tag1,
					 NULL);
	gtk_text_buffer_insert_at_cursor(buffer, "\n\n", 2);
	gtk_text_buffer_get_end_iter(buffer, &end);
	gtk_text_buffer_insert_with_tags(buffer, &end, str_get(&help), -1, tag2,
					 NULL);
	str_free(&help);
}