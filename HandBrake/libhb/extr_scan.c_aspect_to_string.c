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
struct TYPE_3__ {double den; scalar_t__ num; } ;
typedef  TYPE_1__ hb_rational_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static const char *aspect_to_string(hb_rational_t *dar)
{
    double aspect = (double)dar->num / dar->den;
    switch ( (int)(aspect * 9.) )
    {
        case 9 * 4 / 3:    return "4:3";
        case 9 * 16 / 9:   return "16:9";
    }
    static char arstr[32];
    if (aspect >= 1)
        sprintf(arstr, "%.2f:1", aspect);
    else
        sprintf(arstr, "1:%.2f", 1. / aspect );
    return arstr;
}