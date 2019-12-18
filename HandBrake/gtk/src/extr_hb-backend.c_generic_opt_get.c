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
typedef  int /*<<< orphan*/  combo_opts_t ;
typedef  int /*<<< orphan*/  GhbValue ;
typedef  int GhbType ;

/* Variables and functions */
#define  GHB_BOOL 131 
#define  GHB_DOUBLE 130 
#define  GHB_INT 129 
#define  GHB_STRING 128 
 int /*<<< orphan*/ * ghb_double_value_new (double) ; 
 int /*<<< orphan*/ * ghb_int_value_new (int) ; 
 int /*<<< orphan*/ * ghb_string_value_new (char const*) ; 
 double lookup_generic_double (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int lookup_generic_int (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 char* lookup_generic_option (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static GhbValue *
generic_opt_get(const char *name, const void *vopts,
                const GhbValue *gval, GhbType type)
{
    combo_opts_t *opts = (combo_opts_t*)vopts;
    GhbValue *result = NULL;
    switch (type)
    {
        case GHB_INT:
        case GHB_BOOL:
        {
            int val;
            val = lookup_generic_int(opts, gval);
            return ghb_int_value_new(val);
        } break;
        case GHB_DOUBLE:
        {
            double val;
            val = lookup_generic_double(opts, gval);
            return ghb_double_value_new(val);
        } break;
        case GHB_STRING:
        {
            const char *val;
            val = lookup_generic_option(opts, gval);
            return ghb_string_value_new(val);
        } break;
    }
    return result;
}