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
typedef  int /*<<< orphan*/  gint ;
typedef  int /*<<< orphan*/  cairo_t ;
struct TYPE_3__ {int options; int /*<<< orphan*/  doc; } ;
typedef  int /*<<< orphan*/  PopplerPrintFlags ;
typedef  int /*<<< orphan*/  PopplerPage ;
typedef  int PgdPrintOptions ;
typedef  TYPE_1__ PgdPrintDemo ;
typedef  int /*<<< orphan*/  GtkPrintSettings ;
typedef  int /*<<< orphan*/  GtkPrintOperation ;
typedef  int /*<<< orphan*/  GtkPrintContext ;

/* Variables and functions */
 int /*<<< orphan*/  POPPLER_PRINT_DOCUMENT ; 
 int /*<<< orphan*/  POPPLER_PRINT_MARKUP_ANNOTS ; 
 int /*<<< orphan*/  POPPLER_PRINT_STAMP_ANNOTS_ONLY ; 
#define  PRINT_DOCUMENT 130 
#define  PRINT_DOCUMENT_MARKUPS 129 
#define  PRINT_DOCUMENT_STAMPS 128 
 int /*<<< orphan*/  g_assert_not_reached () ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_print_context_get_cairo_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_print_operation_get_print_settings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * poppler_document_get_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poppler_page_render_for_printing_with_options (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pgd_print_draw_page (GtkPrintOperation *op,
		     GtkPrintContext   *context,
		     gint               page_nr,
		     PgdPrintDemo      *demo)
{
	PopplerPage      *page;
	cairo_t          *cr;
        GtkPrintSettings *settings;
        PgdPrintOptions   options;
        PopplerPrintFlags flags = 0;

	page = poppler_document_get_page (demo->doc, page_nr);
	if (!page)
		return;

        settings = gtk_print_operation_get_print_settings (op);
        /* Workaround for gtk+ bug, we need to save the options ourselves */
        options = demo->options;
#if 0
        options = gtk_print_settings_get_int_with_default (settings,
                                                           PGD_PRINT_OPTIONS,
                                                           PRINT_DOCUMENT_MARKUPS);
#endif
        switch (options) {
        case PRINT_DOCUMENT:
                flags |= POPPLER_PRINT_DOCUMENT;
                break;
        case PRINT_DOCUMENT_MARKUPS:
                flags |= POPPLER_PRINT_MARKUP_ANNOTS;
                break;
        case PRINT_DOCUMENT_STAMPS:
                flags |= POPPLER_PRINT_STAMP_ANNOTS_ONLY;
                break;
        default:
                g_assert_not_reached ();
        }

	cr = gtk_print_context_get_cairo_context (context);
	poppler_page_render_for_printing_with_options (page, cr, flags);
	g_object_unref (page);
}