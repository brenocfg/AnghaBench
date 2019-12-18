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
typedef  double gdouble ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 char* g_strdup (int /*<<< orphan*/ ) ; 
 char* g_strdup_printf (char*,double) ; 

__attribute__((used)) static char * get_drc_string(gdouble drc)
{
    char *s_drc;
    if (drc < 0.99)
        s_drc = g_strdup(_("Off"));
    else
        s_drc = g_strdup_printf("%.1f", drc);
    return s_drc;
}