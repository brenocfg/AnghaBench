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
struct TYPE_3__ {int /*<<< orphan*/  doc; } ;
typedef  TYPE_1__ PgdPrintDemo ;
typedef  int /*<<< orphan*/  GtkPrintOperation ;
typedef  int /*<<< orphan*/  GtkPrintContext ;

/* Variables and functions */
 int /*<<< orphan*/  gtk_print_operation_set_n_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poppler_document_get_n_pages (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pgd_print_begin_print (GtkPrintOperation *op,
		       GtkPrintContext   *context,
		       PgdPrintDemo      *demo)
{
	gtk_print_operation_set_n_pages (op, poppler_document_get_n_pages (demo->doc));
}