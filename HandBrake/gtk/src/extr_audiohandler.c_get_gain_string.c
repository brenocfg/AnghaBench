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
 char* g_strdup_printf (char*,...) ; 

__attribute__((used)) static char * get_gain_string(gdouble gain)
{
    char *s_gain;
    if ( gain >= 21.0 )
        s_gain = g_strdup_printf("*11*");
    else
        s_gain = g_strdup_printf(_("%ddB"), (int)gain);
    return s_gain;
}