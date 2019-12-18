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
typedef  int /*<<< orphan*/  tBTA_AG_RES ;
typedef  int UINT16 ;

/* Variables and functions */
#define  BTA_AG_API_AUDIO_CLOSE_EVT 172 
#define  BTA_AG_API_AUDIO_OPEN_EVT 171 
#define  BTA_AG_API_CLOSE_EVT 170 
#define  BTA_AG_API_DEREGISTER_EVT 169 
#define  BTA_AG_API_DISABLE_EVT 168 
#define  BTA_AG_API_ENABLE_EVT 167 
#define  BTA_AG_API_OPEN_EVT 166 
#define  BTA_AG_API_REGISTER_EVT 165 
#define  BTA_AG_API_RESULT_EVT 164 
#define  BTA_AG_API_SETCODEC_EVT 163 
#define  BTA_AG_BINP_RES 162 
#define  BTA_AG_BTRH_RES 161 
#define  BTA_AG_BVRA_RES 160 
#define  BTA_AG_CALL_CANCEL_RES 159 
#define  BTA_AG_CALL_WAIT_RES 158 
#define  BTA_AG_CIND_RES 157 
#define  BTA_AG_CI_RX_WRITE_EVT 156 
#define  BTA_AG_CI_SCO_DATA_EVT 155 
#define  BTA_AG_CI_SLC_READY_EVT 154 
#define  BTA_AG_CLCC_RES 153 
#define  BTA_AG_CNUM_RES 152 
#define  BTA_AG_COPS_RES 151 
#define  BTA_AG_DISC_ACP_RES_EVT 150 
#define  BTA_AG_DISC_FAIL_EVT 149 
#define  BTA_AG_DISC_INT_RES_EVT 148 
#define  BTA_AG_DISC_OK_EVT 147 
#define  BTA_AG_END_CALL_RES 146 
#define  BTA_AG_INBAND_RING_RES 145 
#define  BTA_AG_IND_RES 144 
#define  BTA_AG_IN_CALL_CONN_RES 143 
#define  BTA_AG_IN_CALL_RES 142 
#define  BTA_AG_MIC_RES 141 
#define  BTA_AG_OUT_CALL_ALERT_RES 140 
#define  BTA_AG_OUT_CALL_CONN_RES 139 
#define  BTA_AG_OUT_CALL_ORIG_RES 138 
#define  BTA_AG_RFC_CLOSE_EVT 137 
#define  BTA_AG_RFC_DATA_EVT 136 
#define  BTA_AG_RFC_OPEN_EVT 135 
#define  BTA_AG_RFC_SRV_CLOSE_EVT 134 
#define  BTA_AG_RING_TOUT_EVT 133 
#define  BTA_AG_SCO_CLOSE_EVT 132 
#define  BTA_AG_SCO_OPEN_EVT 131 
#define  BTA_AG_SPK_RES 130 
#define  BTA_AG_SVC_TOUT_EVT 129 
#define  BTA_AG_UNAT_RES 128 

__attribute__((used)) static char *bta_ag_evt_str(UINT16 event, tBTA_AG_RES result)
{
    switch (event)
    {
    case BTA_AG_API_REGISTER_EVT:
        return "Register Request";
    case BTA_AG_API_DEREGISTER_EVT:
        return "Deregister Request";
    case BTA_AG_API_OPEN_EVT:
        return "Open SLC Request";
    case BTA_AG_API_CLOSE_EVT:
        return "Close SLC Request";
    case BTA_AG_API_AUDIO_OPEN_EVT:
        return "Open Audio Request";
    case BTA_AG_API_AUDIO_CLOSE_EVT:
        return "Close Audio Request";
    case BTA_AG_API_RESULT_EVT:
        switch (result) {
            case BTA_AG_SPK_RES:            return ("AT Result  BTA_AG_SPK_RES");
            case BTA_AG_MIC_RES:            return ("AT Result  BTA_AG_MIC_RES");
            case BTA_AG_INBAND_RING_RES:    return ("AT Result  BTA_AG_INBAND_RING_RES");
            case BTA_AG_CIND_RES:           return ("AT Result  BTA_AG_CIND_RES");
            case BTA_AG_BINP_RES:           return ("AT Result  BTA_AG_BINP_RES");
            case BTA_AG_IND_RES:            return ("AT Result  BTA_AG_IND_RES");
            case BTA_AG_BVRA_RES:           return ("AT Result  BTA_AG_BVRA_RES");
            case BTA_AG_CNUM_RES:           return ("AT Result  BTA_AG_CNUM_RES");
            case BTA_AG_BTRH_RES:           return ("AT Result  BTA_AG_BTRH_RES");
            case BTA_AG_CLCC_RES:           return ("AT Result  BTA_AG_CLCC_RES");
            case BTA_AG_COPS_RES:           return ("AT Result  BTA_AG_COPS_RES");
            case BTA_AG_IN_CALL_RES:        return ("AT Result  BTA_AG_IN_CALL_RES");
            case BTA_AG_IN_CALL_CONN_RES:   return ("AT Result  BTA_AG_IN_CALL_CONN_RES");
            case BTA_AG_CALL_WAIT_RES:      return ("AT Result  BTA_AG_CALL_WAIT_RES");
            case BTA_AG_OUT_CALL_ORIG_RES:  return ("AT Result  BTA_AG_OUT_CALL_ORIG_RES");
            case BTA_AG_OUT_CALL_ALERT_RES: return ("AT Result  BTA_AG_OUT_CALL_ALERT_RES");
            case BTA_AG_OUT_CALL_CONN_RES:  return ("AT Result  BTA_AG_OUT_CALL_CONN_RES");
            case BTA_AG_CALL_CANCEL_RES:    return ("AT Result  BTA_AG_CALL_CANCEL_RES");
            case BTA_AG_END_CALL_RES:       return ("AT Result  BTA_AG_END_CALL_RES");
            case BTA_AG_UNAT_RES:           return ("AT Result  BTA_AG_UNAT_RES");
            default:                        return ("Unknown AG Result");
        }
    case BTA_AG_API_SETCODEC_EVT:
        return "Set Codec Request";
    case BTA_AG_RFC_OPEN_EVT:
        return "RFC Opened";
    case BTA_AG_RFC_CLOSE_EVT:
        return "RFC Closed";
    case BTA_AG_RFC_SRV_CLOSE_EVT:
        return "RFC SRV Closed";
    case BTA_AG_RFC_DATA_EVT:
        return "RFC Data";
    case BTA_AG_SCO_OPEN_EVT:
        return "Audio Opened";
    case BTA_AG_SCO_CLOSE_EVT:
        return "Audio Closed";
    case BTA_AG_DISC_ACP_RES_EVT:
        return "Discovery ACP Result";
    case BTA_AG_DISC_INT_RES_EVT:
        return "Discovery INT Result";
    case BTA_AG_DISC_OK_EVT:
        return "Discovery OK";
    case BTA_AG_DISC_FAIL_EVT:
        return "Discovery Failed";
    case BTA_AG_CI_RX_WRITE_EVT:
        return "CI RX Write";
    case BTA_AG_RING_TOUT_EVT:
        return "Ring Timeout";
    case BTA_AG_SVC_TOUT_EVT:
        return "Service Timeout";
    case BTA_AG_API_ENABLE_EVT:
        return "Enable AG";
    case BTA_AG_API_DISABLE_EVT:
        return "Disable AG";
    case BTA_AG_CI_SCO_DATA_EVT:
        return "SCO data Callin";
    case BTA_AG_CI_SLC_READY_EVT:
        return "SLC Ready Callin";
    default:
        return "Unknown AG Event";
    }
}