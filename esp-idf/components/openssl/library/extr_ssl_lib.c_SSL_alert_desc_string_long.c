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

const char* SSL_alert_desc_string_long(int value)
{
    const char *str;

    switch (value & 0xff)
    {
        case SSL3_AD_CLOSE_NOTIFY:
            str = "close notify";
            break;
        case SSL3_AD_UNEXPECTED_MESSAGE:
            str = "unexpected_message";
            break;
        case SSL3_AD_BAD_RECORD_MAC:
            str = "bad record mac";
            break;
        case SSL3_AD_DECOMPRESSION_FAILURE:
            str = "decompression failure";
            break;
        case SSL3_AD_HANDSHAKE_FAILURE:
            str = "handshake failure";
            break;
        case SSL3_AD_NO_CERTIFICATE:
            str = "no certificate";
            break;
        case SSL3_AD_BAD_CERTIFICATE:
            str = "bad certificate";
            break;
        case SSL3_AD_UNSUPPORTED_CERTIFICATE:
            str = "unsupported certificate";
            break;
        case SSL3_AD_CERTIFICATE_REVOKED:
            str = "certificate revoked";
            break;
        case SSL3_AD_CERTIFICATE_EXPIRED:
            str = "certificate expired";
            break;
        case SSL3_AD_CERTIFICATE_UNKNOWN:
            str = "certificate unknown";
            break;
        case SSL3_AD_ILLEGAL_PARAMETER:
            str = "illegal parameter";
            break;
        case TLS1_AD_DECRYPTION_FAILED:
            str = "decryption failed";
            break;
        case TLS1_AD_RECORD_OVERFLOW:
            str = "record overflow";
            break;
        case TLS1_AD_UNKNOWN_CA:
            str = "unknown CA";
            break;
        case TLS1_AD_ACCESS_DENIED:
            str = "access denied";
            break;
        case TLS1_AD_DECODE_ERROR:
            str = "decode error";
            break;
        case TLS1_AD_DECRYPT_ERROR:
            str = "decrypt error";
            break;
        case TLS1_AD_EXPORT_RESTRICTION:
            str = "export restriction";
            break;
        case TLS1_AD_PROTOCOL_VERSION:
            str = "protocol version";
            break;
        case TLS1_AD_INSUFFICIENT_SECURITY:
            str = "insufficient security";
            break;
        case TLS1_AD_INTERNAL_ERROR:
            str = "internal error";
            break;
        case TLS1_AD_USER_CANCELLED:
            str = "user canceled";
            break;
        case TLS1_AD_NO_RENEGOTIATION:
            str = "no renegotiation";
            break;
        case TLS1_AD_UNSUPPORTED_EXTENSION:
            str = "unsupported extension";
            break;
        case TLS1_AD_CERTIFICATE_UNOBTAINABLE:
            str = "certificate unobtainable";
            break;
        case TLS1_AD_UNRECOGNIZED_NAME:
            str = "unrecognized name";
            break;
        case TLS1_AD_BAD_CERTIFICATE_STATUS_RESPONSE:
            str = "bad certificate status response";
            break;
        case TLS1_AD_BAD_CERTIFICATE_HASH_VALUE:
            str = "bad certificate hash value";
            break;
        case TLS1_AD_UNKNOWN_PSK_IDENTITY:
            str = "unknown PSK identity";
            break;
        default:
            str = "unknown";
            break;
    }

    return str;
}