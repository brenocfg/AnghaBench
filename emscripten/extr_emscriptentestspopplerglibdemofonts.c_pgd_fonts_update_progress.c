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
typedef  int gint ;
typedef  int gdouble ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_3__ {int /*<<< orphan*/  progress; } ;
typedef  TYPE_1__ PgdFontsDemo ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_PROGRESS_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN (int,double) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_progress_bar_set_fraction (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_progress_bar_set_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_fonts_update_progress (PgdFontsDemo *demo,
			   gint          n_pages,
			   gint          scanned)
{
	gchar *str;

	str = g_strdup_printf ("Scanning fonts (%d%%)",
			       MIN (scanned * 100 / n_pages, 100));
	gtk_progress_bar_set_text (GTK_PROGRESS_BAR (demo->progress), str);
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (demo->progress),
				       MIN ((gdouble)scanned / n_pages, 1.0));
	g_free (str);
}