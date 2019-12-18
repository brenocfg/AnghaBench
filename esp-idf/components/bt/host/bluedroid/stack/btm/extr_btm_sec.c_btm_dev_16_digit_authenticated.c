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
struct TYPE_3__ {int sec_flags; } ;
typedef  TYPE_1__ tBTM_SEC_DEV_REC ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int BTM_SEC_16_DIGIT_PIN_AUTHED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN btm_dev_16_digit_authenticated(tBTM_SEC_DEV_REC *p_dev_rec)
{
    // BTM_SEC_16_DIGIT_PIN_AUTHED is set if MITM or 16 digit pin is used
    if (p_dev_rec->sec_flags & BTM_SEC_16_DIGIT_PIN_AUTHED) {
        return (TRUE);
    }
    return (FALSE);
}