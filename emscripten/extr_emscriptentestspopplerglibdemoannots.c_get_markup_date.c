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
typedef  scalar_t__ time_t ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  PopplerAnnotMarkup ;
typedef  int /*<<< orphan*/  GDate ;

/* Variables and functions */
 int /*<<< orphan*/  g_date_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_date_to_struct_tm (int /*<<< orphan*/ *,struct tm*) ; 
 scalar_t__ mktime (struct tm*) ; 
 int /*<<< orphan*/ * pgd_format_date (scalar_t__) ; 
 int /*<<< orphan*/ * poppler_annot_markup_get_date (int /*<<< orphan*/ *) ; 

gchar *
get_markup_date (PopplerAnnotMarkup *poppler_annot)
{
    GDate *date;
    struct tm t;
    time_t timet;

    date = poppler_annot_markup_get_date (poppler_annot);
    if (!date)
	    return NULL;

    g_date_to_struct_tm (date, &t);
    g_date_free (date);

    timet = mktime (&t);
    return timet == (time_t) - 1 ? NULL : pgd_format_date (timet);
}