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
typedef  int INT16 ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int utl_str2int (char*) ; 

__attribute__((used)) static BOOLEAN bta_ag_parse_cmer(char *p_s, BOOLEAN *p_enabled)
{
    INT16   n[4] = {-1, -1, -1, -1};
    int     i;
    char    *p;

    for (i = 0; i < 4; i++) {
        /* skip to comma delimiter */
        for (p = p_s; *p != ',' && *p != 0; p++);
        /* get integer value */
        *p = 0;
        n[i] = utl_str2int(p_s);
        p_s = p + 1;
        if (p_s == 0) {
            break;
        }
    }
    /* process values */
    if (n[0] < 0 || n[3] < 0) {
        return FALSE;
    }
    if ((n[0] == 3) && ((n[3] == 1) || (n[3] == 0))) {
        *p_enabled = (BOOLEAN) n[3];
    }
    return TRUE;
}