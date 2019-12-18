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
typedef  int /*<<< orphan*/  tBTA_AG_SCB ;
typedef  scalar_t__ UINT8 ;
typedef  int INT16 ;

/* Variables and functions */
 scalar_t__ BTA_AG_INVALID_CHLD ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 int utl_str2int (char*) ; 

__attribute__((used)) static UINT8 bta_ag_parse_chld(tBTA_AG_SCB *p_scb, char *p_s)
{
    UINT8   retval = 0;
    INT16   idx = -1;
    UNUSED(p_scb);

    if (!isdigit(p_s[0])) {
        return BTA_AG_INVALID_CHLD;
    }

    if (p_s[1] != 0) {
        /* p_idxstr++;  point to beginning of call number */
        idx = utl_str2int(&p_s[1]);
        if (idx != -1 && idx < 255) {
            retval = (UINT8)idx;
        } else {
            retval = BTA_AG_INVALID_CHLD;
        }
    }
    return(retval);
}