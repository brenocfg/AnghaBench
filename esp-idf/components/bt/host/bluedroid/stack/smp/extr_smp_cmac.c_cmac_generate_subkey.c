#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tSMP_ENC ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ BT_OCTET16 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BT_OCTET16_LEN ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SMP_Encrypt (TYPE_1__,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SMP_TRACE_EVENT (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cmac_subkey_cont (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOLEAN cmac_generate_subkey(BT_OCTET16 key)
{
    BT_OCTET16 z = {0};
    BOOLEAN     ret = TRUE;
    tSMP_ENC output;
    SMP_TRACE_EVENT (" cmac_generate_subkey");

    if (SMP_Encrypt(key, BT_OCTET16_LEN, z, BT_OCTET16_LEN, &output)) {
        cmac_subkey_cont(&output);;
    } else {
        ret = FALSE;
    }

    return ret;
}