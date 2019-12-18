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
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_DOUBLE ; 
 int /*<<< orphan*/  ghb_value_free (int /*<<< orphan*/ **) ; 
 double ghb_value_get_double (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lookup_combo_value (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

gdouble
ghb_lookup_combo_double(const gchar *name, const GhbValue *gval)
{
    if (gval == NULL)
        return 0;
    GhbValue *gresult = lookup_combo_value(name, gval, GHB_DOUBLE);
    double result = ghb_value_get_double(gresult);
    ghb_value_free(&gresult);
    return result;
}