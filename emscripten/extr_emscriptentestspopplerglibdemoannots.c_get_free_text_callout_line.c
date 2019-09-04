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
typedef  int /*<<< orphan*/  gdouble ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_3__ {int /*<<< orphan*/  y3; int /*<<< orphan*/  x3; scalar_t__ multiline; int /*<<< orphan*/  y2; int /*<<< orphan*/  x2; int /*<<< orphan*/  y1; int /*<<< orphan*/  x1; } ;
typedef  int /*<<< orphan*/  PopplerAnnotFreeText ;
typedef  TYPE_1__ PopplerAnnotCalloutLine ;

/* Variables and functions */
 int /*<<< orphan*/ * g_strdup_printf (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 TYPE_1__* poppler_annot_free_text_get_callout_line (int /*<<< orphan*/ *) ; 

gchar *
get_free_text_callout_line (PopplerAnnotFreeText *poppler_annot)
{
    PopplerAnnotCalloutLine *callout;
    gdouble x1, y1, x2, y2;
    gchar *text;
    
    if ((callout = poppler_annot_free_text_get_callout_line (poppler_annot))) {
        text = g_strdup_printf ("%f,%f,%f,%f", callout->x1,
                                               callout->y1,
                                               callout->x2,
                                               callout->y2);
        if (callout->multiline)
            text = g_strdup_printf ("%s,%f,%f", text,
                                                callout->x3,
                                                callout->y3);

        return text;
    }
    
    return NULL;
}