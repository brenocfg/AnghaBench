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

/* Variables and functions */
#define  L2CEVT_ACK_TIMEOUT 160 
#define  L2CEVT_L2CAP_CONFIG_REQ 159 
#define  L2CEVT_L2CAP_CONFIG_RSP 158 
#define  L2CEVT_L2CAP_CONFIG_RSP_NEG 157 
#define  L2CEVT_L2CAP_CONNECT_REQ 156 
#define  L2CEVT_L2CAP_CONNECT_RSP 155 
#define  L2CEVT_L2CAP_CONNECT_RSP_NEG 154 
#define  L2CEVT_L2CAP_CONNECT_RSP_PND 153 
#define  L2CEVT_L2CAP_DATA 152 
#define  L2CEVT_L2CAP_DISCONNECT_REQ 151 
#define  L2CEVT_L2CAP_DISCONNECT_RSP 150 
#define  L2CEVT_L2CAP_INFO_RSP 149 
#define  L2CEVT_L2CA_CONFIG_REQ 148 
#define  L2CEVT_L2CA_CONFIG_RSP 147 
#define  L2CEVT_L2CA_CONFIG_RSP_NEG 146 
#define  L2CEVT_L2CA_CONNECT_REQ 145 
#define  L2CEVT_L2CA_CONNECT_RSP 144 
#define  L2CEVT_L2CA_CONNECT_RSP_NEG 143 
#define  L2CEVT_L2CA_DATA_READ 142 
#define  L2CEVT_L2CA_DATA_WRITE 141 
#define  L2CEVT_L2CA_DISCONNECT_REQ 140 
#define  L2CEVT_L2CA_DISCONNECT_RSP 139 
#define  L2CEVT_LP_CONNECT_CFM 138 
#define  L2CEVT_LP_CONNECT_CFM_NEG 137 
#define  L2CEVT_LP_CONNECT_IND 136 
#define  L2CEVT_LP_DISCONNECT_IND 135 
#define  L2CEVT_LP_QOS_CFM 134 
#define  L2CEVT_LP_QOS_CFM_NEG 133 
#define  L2CEVT_LP_QOS_VIOLATION_IND 132 
#define  L2CEVT_SEC_COMP 131 
#define  L2CEVT_SEC_COMP_NEG 130 
#define  L2CEVT_SEC_RE_SEND_CMD 129 
#define  L2CEVT_TIMEOUT 128 

__attribute__((used)) static char *l2c_csm_get_event_name (UINT16 event)
{
    switch (event) {
    case L2CEVT_LP_CONNECT_CFM:                  /* Lower layer connect confirm          */
        return ("LOWER_LAYER_CONNECT_CFM");
    case L2CEVT_LP_CONNECT_CFM_NEG:              /* Lower layer connect confirm (failed) */
        return ("LOWER_LAYER_CONNECT_CFM_NEG");
    case L2CEVT_LP_CONNECT_IND:                  /* Lower layer connect indication       */
        return ("LOWER_LAYER_CONNECT_IND");
    case L2CEVT_LP_DISCONNECT_IND:               /* Lower layer disconnect indication    */
        return ("LOWER_LAYER_DISCONNECT_IND");
    case L2CEVT_LP_QOS_CFM:                      /* Lower layer QOS confirmation         */
        return ("LOWER_LAYER_QOS_CFM");
    case L2CEVT_LP_QOS_CFM_NEG:                  /* Lower layer QOS confirmation (failed)*/
        return ("LOWER_LAYER_QOS_CFM_NEG");
    case L2CEVT_LP_QOS_VIOLATION_IND:            /* Lower layer QOS violation indication */
        return ("LOWER_LAYER_QOS_VIOLATION_IND");

    case L2CEVT_SEC_COMP:                        /* Security cleared successfully        */
        return ("SECURITY_COMPLETE");
    case L2CEVT_SEC_COMP_NEG:                    /* Security procedure failed            */
        return ("SECURITY_COMPLETE_NEG");

    case L2CEVT_L2CAP_CONNECT_REQ:               /* Peer connection request              */
        return ("PEER_CONNECT_REQ");
    case L2CEVT_L2CAP_CONNECT_RSP:               /* Peer connection response             */
        return ("PEER_CONNECT_RSP");
    case L2CEVT_L2CAP_CONNECT_RSP_PND:           /* Peer connection response pending     */
        return ("PEER_CONNECT_RSP_PND");
    case L2CEVT_L2CAP_CONNECT_RSP_NEG:           /* Peer connection response (failed)    */
        return ("PEER_CONNECT_RSP_NEG");
    case L2CEVT_L2CAP_CONFIG_REQ:                /* Peer configuration request           */
        return ("PEER_CONFIG_REQ");
    case L2CEVT_L2CAP_CONFIG_RSP:                /* Peer configuration response          */
        return ("PEER_CONFIG_RSP");
    case L2CEVT_L2CAP_CONFIG_RSP_NEG:            /* Peer configuration response (failed) */
        return ("PEER_CONFIG_RSP_NEG");
    case L2CEVT_L2CAP_DISCONNECT_REQ:            /* Peer disconnect request              */
        return ("PEER_DISCONNECT_REQ");
    case L2CEVT_L2CAP_DISCONNECT_RSP:            /* Peer disconnect response             */
        return ("PEER_DISCONNECT_RSP");
    case L2CEVT_L2CAP_DATA:                      /* Peer data                            */
        return ("PEER_DATA");

    case L2CEVT_L2CA_CONNECT_REQ:                /* Upper layer connect request          */
        return ("UPPER_LAYER_CONNECT_REQ");
    case L2CEVT_L2CA_CONNECT_RSP:                /* Upper layer connect response         */
        return ("UPPER_LAYER_CONNECT_RSP");
    case L2CEVT_L2CA_CONNECT_RSP_NEG:            /* Upper layer connect response (failed)*/
        return ("UPPER_LAYER_CONNECT_RSP_NEG");
    case L2CEVT_L2CA_CONFIG_REQ:                 /* Upper layer config request           */
        return ("UPPER_LAYER_CONFIG_REQ");
    case L2CEVT_L2CA_CONFIG_RSP:                 /* Upper layer config response          */
        return ("UPPER_LAYER_CONFIG_RSP");
    case L2CEVT_L2CA_CONFIG_RSP_NEG:             /* Upper layer config response (failed) */
        return ("UPPER_LAYER_CONFIG_RSP_NEG");
    case L2CEVT_L2CA_DISCONNECT_REQ:             /* Upper layer disconnect request       */
        return ("UPPER_LAYER_DISCONNECT_REQ");
    case L2CEVT_L2CA_DISCONNECT_RSP:             /* Upper layer disconnect response      */
        return ("UPPER_LAYER_DISCONNECT_RSP");
    case L2CEVT_L2CA_DATA_READ:                  /* Upper layer data read                */
        return ("UPPER_LAYER_DATA_READ");
    case L2CEVT_L2CA_DATA_WRITE:                 /* Upper layer data write               */
        return ("UPPER_LAYER_DATA_WRITE");
    case L2CEVT_TIMEOUT:                         /* Timeout                              */
        return ("TIMEOUT");
    case L2CEVT_SEC_RE_SEND_CMD:
        return ("SEC_RE_SEND_CMD");
    case L2CEVT_L2CAP_INFO_RSP:                  /* Peer information response            */
        return ("L2CEVT_L2CAP_INFO_RSP");
    case L2CEVT_ACK_TIMEOUT:
        return ("L2CEVT_ACK_TIMEOUT");

    default:
        return ("???? UNKNOWN EVENT");
    }
}