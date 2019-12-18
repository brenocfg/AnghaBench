#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ p_eir; } ;
struct TYPE_5__ {TYPE_1__ inq_res; } ;
typedef  TYPE_2__ tBTA_DM_SEARCH ;
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ BD_NAME_LEN ; 
 scalar_t__* BTM_CheckEirData (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  BTM_EIR_COMPLETE_LOCAL_NAME_TYPE ; 
 int /*<<< orphan*/  BTM_EIR_SHORTENED_LOCAL_NAME_TYPE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static BOOLEAN check_eir_remote_name(tBTA_DM_SEARCH *p_search_data,
                                     UINT8 *p_remote_name, UINT8 *p_remote_name_len)
{
    UINT8 *p_eir_remote_name = NULL;
    UINT8 remote_name_len = 0;

    /* Check EIR for remote name and services */
    if (p_search_data->inq_res.p_eir) {
        p_eir_remote_name = BTM_CheckEirData(p_search_data->inq_res.p_eir,
                                             BTM_EIR_COMPLETE_LOCAL_NAME_TYPE, &remote_name_len);
        if (!p_eir_remote_name) {
            p_eir_remote_name = BTM_CheckEirData(p_search_data->inq_res.p_eir,
                                                 BTM_EIR_SHORTENED_LOCAL_NAME_TYPE, &remote_name_len);
        }

        if (p_eir_remote_name) {
            if (remote_name_len > BD_NAME_LEN) {
                remote_name_len = BD_NAME_LEN;
            }

            if (p_remote_name && p_remote_name_len) {
                memcpy(p_remote_name, p_eir_remote_name, remote_name_len);
                *(p_remote_name + remote_name_len) = 0;
                *p_remote_name_len = remote_name_len;
            }

            return TRUE;
        }
    }

    return FALSE;

}