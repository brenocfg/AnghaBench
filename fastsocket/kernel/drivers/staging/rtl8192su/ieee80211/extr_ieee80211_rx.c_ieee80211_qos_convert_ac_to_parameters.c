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
typedef  int u8 ;
struct ieee80211_qos_parameters {int* aifs; int* cw_min; int* cw_max; int* flag; int /*<<< orphan*/ * tx_op_limit; } ;
struct ieee80211_qos_parameter_info {struct ieee80211_qos_ac_parameter* ac_params_record; } ;
struct ieee80211_qos_ac_parameter {int aci_aifsn; int ecw_min_max; int /*<<< orphan*/  tx_op_limit; } ;

/* Variables and functions */
 int QOS_QUEUE_NUM ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ieee80211_qos_convert_ac_to_parameters(struct
                                                  ieee80211_qos_parameter_info
                                                  *param_elm, struct
                                                  ieee80211_qos_parameters
                                                  *qos_param)
{
        int rc = 0;
        int i;
        struct ieee80211_qos_ac_parameter *ac_params;
	u8 aci;
        //u8 cw_min;
        //u8 cw_max;

        for (i = 0; i < QOS_QUEUE_NUM; i++) {
                ac_params = &(param_elm->ac_params_record[i]);

		aci = (ac_params->aci_aifsn & 0x60) >> 5;

		if(aci >= QOS_QUEUE_NUM)
			continue;
                qos_param->aifs[aci] = (ac_params->aci_aifsn) & 0x0f;

		/* WMM spec P.11: The minimum value for AIFSN shall be 2 */
                qos_param->aifs[aci] = (qos_param->aifs[aci] < 2) ? 2:qos_param->aifs[aci];

                qos_param->cw_min[aci] = ac_params->ecw_min_max & 0x0F;

                qos_param->cw_max[aci] = (ac_params->ecw_min_max & 0xF0) >> 4;

                qos_param->flag[aci] =
                    (ac_params->aci_aifsn & 0x10) ? 0x01 : 0x00;
                qos_param->tx_op_limit[aci] = le16_to_cpu(ac_params->tx_op_limit);
        }
        return rc;
}