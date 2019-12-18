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

/* Variables and functions */
#define  SSL3_AD_BAD_CERTIFICATE 157 
#define  SSL3_AD_BAD_RECORD_MAC 156 
#define  SSL3_AD_CERTIFICATE_EXPIRED 155 
#define  SSL3_AD_CERTIFICATE_REVOKED 154 
#define  SSL3_AD_CERTIFICATE_UNKNOWN 153 
#define  SSL3_AD_CLOSE_NOTIFY 152 
#define  SSL3_AD_DECOMPRESSION_FAILURE 151 
#define  SSL3_AD_HANDSHAKE_FAILURE 150 
#define  SSL3_AD_ILLEGAL_PARAMETER 149 
#define  SSL3_AD_NO_CERTIFICATE 148 
#define  SSL3_AD_UNEXPECTED_MESSAGE 147 
#define  SSL3_AD_UNSUPPORTED_CERTIFICATE 146 
#define  TLS1_AD_ACCESS_DENIED 145 
#define  TLS1_AD_BAD_CERTIFICATE_HASH_VALUE 144 
#define  TLS1_AD_BAD_CERTIFICATE_STATUS_RESPONSE 143 
#define  TLS1_AD_CERTIFICATE_UNOBTAINABLE 142 
#define  TLS1_AD_DECODE_ERROR 141 
#define  TLS1_AD_DECRYPTION_FAILED 140 
#define  TLS1_AD_DECRYPT_ERROR 139 
#define  TLS1_AD_EXPORT_RESTRICTION 138 
#define  TLS1_AD_INSUFFICIENT_SECURITY 137 
#define  TLS1_AD_INTERNAL_ERROR 136 
#define  TLS1_AD_NO_RENEGOTIATION 135 
#define  TLS1_AD_PROTOCOL_VERSION 134 
#define  TLS1_AD_RECORD_OVERFLOW 133 
#define  TLS1_AD_UNKNOWN_CA 132 
#define  TLS1_AD_UNKNOWN_PSK_IDENTITY 131 
#define  TLS1_AD_UNRECOGNIZED_NAME 130 
#define  TLS1_AD_UNSUPPORTED_EXTENSION 129 
#define  TLS1_AD_USER_CANCELLED 128 

const char* SSL_alert_desc_string(int value)
{
    const char *str;

    switch (value & 0xff)
    {
        case SSL3_AD_CLOSE_NOTIFY:
            str = "CN";
            break;
        case SSL3_AD_UNEXPECTED_MESSAGE:
            str = "UM";
            break;
        case SSL3_AD_BAD_RECORD_MAC:
            str = "BM";
            break;
        case SSL3_AD_DECOMPRESSION_FAILURE:
            str = "DF";
            break;
        case SSL3_AD_HANDSHAKE_FAILURE:
            str = "HF";
            break;
        case SSL3_AD_NO_CERTIFICATE:
            str = "NC";
            break;
        case SSL3_AD_BAD_CERTIFICATE:
            str = "BC";
            break;
        case SSL3_AD_UNSUPPORTED_CERTIFICATE:
            str = "UC";
            break;
        case SSL3_AD_CERTIFICATE_REVOKED:
            str = "CR";
            break;
        case SSL3_AD_CERTIFICATE_EXPIRED:
            str = "CE";
            break;
        case SSL3_AD_CERTIFICATE_UNKNOWN:
            str = "CU";
            break;
        case SSL3_AD_ILLEGAL_PARAMETER:
            str = "IP";
            break;
        case TLS1_AD_DECRYPTION_FAILED:
            str = "DC";
            break;
        case TLS1_AD_RECORD_OVERFLOW:
            str = "RO";
            break;
        case TLS1_AD_UNKNOWN_CA:
            str = "CA";
            break;
        case TLS1_AD_ACCESS_DENIED:
            str = "AD";
            break;
        case TLS1_AD_DECODE_ERROR:
            str = "DE";
            break;
        case TLS1_AD_DECRYPT_ERROR:
            str = "CY";
            break;
        case TLS1_AD_EXPORT_RESTRICTION:
            str = "ER";
            break;
        case TLS1_AD_PROTOCOL_VERSION:
            str = "PV";
            break;
        case TLS1_AD_INSUFFICIENT_SECURITY:
            str = "IS";
            break;
        case TLS1_AD_INTERNAL_ERROR:
            str = "IE";
            break;
        case TLS1_AD_USER_CANCELLED:
            str = "US";
            break;
        case TLS1_AD_NO_RENEGOTIATION:
            str = "NR";
            break;
        case TLS1_AD_UNSUPPORTED_EXTENSION:
            str = "UE";
            break;
        case TLS1_AD_CERTIFICATE_UNOBTAINABLE:
            str = "CO";
            break;
        case TLS1_AD_UNRECOGNIZED_NAME:
            str = "UN";
            break;
        case TLS1_AD_BAD_CERTIFICATE_STATUS_RESPONSE:
            str = "BR";
            break;
        case TLS1_AD_BAD_CERTIFICATE_HASH_VALUE:
            str = "BH";
            break;
        case TLS1_AD_UNKNOWN_PSK_IDENTITY:
            str = "UP";
            break;
        default:
            str = "UK";
            break;
    }

    return str;
}