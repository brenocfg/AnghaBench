#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  page; int /*<<< orphan*/  doc; } ;
typedef  int /*<<< orphan*/  PopplerPage ;
typedef  TYPE_1__ PgdPageDemo ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_page_set_page (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * poppler_document_get_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pgd_page_get_info (GtkWidget   *button,
		   PgdPageDemo *demo)
{
	PopplerPage *page;

	page = poppler_document_get_page (demo->doc, demo->page);
	pgd_page_set_page (demo, page);
	g_object_unref (page);
}