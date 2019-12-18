#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int cipher_suite; } ;
struct tlsv1_server {TYPE_1__ rl; } ;

/* Variables and functions */
#define  TLS_DH_anon_WITH_AES_128_CBC_SHA 134 
#define  TLS_RSA_WITH_3DES_EDE_CBC_SHA 133 
#define  TLS_RSA_WITH_AES_128_CBC_SHA 132 
#define  TLS_RSA_WITH_AES_256_CBC_SHA 131 
#define  TLS_RSA_WITH_DES_CBC_SHA 130 
#define  TLS_RSA_WITH_RC4_128_MD5 129 
#define  TLS_RSA_WITH_RC4_128_SHA 128 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int tlsv1_server_get_cipher(struct tlsv1_server *conn, char *buf,
			    size_t buflen)
{
#ifndef ESPRESSIF_USE	
    char *cipher;

	switch (conn->rl.cipher_suite) {
	case TLS_RSA_WITH_RC4_128_MD5:
		cipher = "RC4-MD5";
		break;
	case TLS_RSA_WITH_RC4_128_SHA:
		cipher = "RC4-SHA";
		break;
#ifdef CONFIG_DES
	case TLS_RSA_WITH_DES_CBC_SHA:
		cipher = "DES-CBC-SHA";
		break;
#endif
#ifdef CONFIG_DES3
	case TLS_RSA_WITH_3DES_EDE_CBC_SHA:
		cipher = "DES-CBC3-SHA";
		break;
#endif
	case TLS_DH_anon_WITH_AES_128_CBC_SHA:
		cipher = "ADH-AES-128-SHA";
		break;
	case TLS_RSA_WITH_AES_256_CBC_SHA:
		cipher = "AES-256-SHA";
		break;
	case TLS_RSA_WITH_AES_128_CBC_SHA:
		cipher = "AES-128-SHA";
		break;
	default:
		return -1;
	}

	//if (os_strlcpy(buf, cipher, buflen) >= buflen)
	//	return -1;

	os_memcpy((u8 *)buf, (u8 *)cipher, buflen);

	return 0;
#else
    char cipher[20];

    switch (conn->rl.cipher_suite) {
        case TLS_RSA_WITH_RC4_128_MD5:
		    strcpy(cipher, "RC4-MD5");
		    break;
        case TLS_RSA_WITH_RC4_128_SHA:
            strcpy(cipher, "RC4-SHA");
            break;
        case TLS_RSA_WITH_DES_CBC_SHA:
            strcpy(cipher, "DES-CBC-SHA");
            break;
        case TLS_RSA_WITH_3DES_EDE_CBC_SHA:
            strcpy(cipher, "DES-CBC3-SHA");
            break;
        case TLS_DH_anon_WITH_AES_128_CBC_SHA:
            strcpy(cipher, "ADH-AES-128-SHA");
            break;
        case TLS_RSA_WITH_AES_256_CBC_SHA:
            strcpy(cipher, "AES-256-SHA");
            break;
        case TLS_RSA_WITH_AES_128_CBC_SHA:
            strcpy(cipher, "AES-128-SHA");
            break;
        default:
            return -1;
	}
    os_memcpy((u8 *)buf, (u8 *)cipher, buflen);

    return 0;
#endif
}