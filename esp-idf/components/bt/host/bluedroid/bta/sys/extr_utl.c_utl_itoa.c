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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT16 ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 

UINT8 utl_itoa(UINT16 i, char *p_s)
{
    UINT16  j, k;
    char    *p = p_s;
    BOOLEAN fill = FALSE;

    if (i == 0) {
        /* take care of zero case */
        *p++ = '0';
    } else {
        for (j = 10000; j > 0; j /= 10) {
            k = i / j;
            i %= j;
            if (k > 0 || fill) {
                *p++ = k + '0';
                fill = TRUE;
            }
        }
    }
    *p = 0;
    return (UINT8) (p - p_s);
}