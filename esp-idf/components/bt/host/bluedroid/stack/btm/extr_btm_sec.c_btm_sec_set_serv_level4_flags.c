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
typedef  int UINT16 ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int BTM_SEC_IN_LEVEL4_FLAGS ; 
 int BTM_SEC_OUT_LEVEL4_FLAGS ; 

__attribute__((used)) static UINT16 btm_sec_set_serv_level4_flags(UINT16 cur_security, BOOLEAN is_originator)
{
    UINT16  sec_level4_flags = is_originator ? BTM_SEC_OUT_LEVEL4_FLAGS : BTM_SEC_IN_LEVEL4_FLAGS;

    return cur_security | sec_level4_flags;
}