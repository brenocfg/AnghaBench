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
struct tls_connection_params {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLS_CONN_ALLOW_SIGN_RSA_MD5 ; 
 int /*<<< orphan*/  TLS_CONN_DISABLE_SESSION_TICKET ; 
 int /*<<< orphan*/  TLS_CONN_DISABLE_TIME_CHECKS ; 
 scalar_t__ os_strstr (char const*,char*) ; 

__attribute__((used)) static void eap_tls_params_flags(struct tls_connection_params *params,
				 const char *txt)
{
	if (txt == NULL)
		return;
	if (os_strstr(txt, "tls_allow_md5=1"))
		params->flags |= TLS_CONN_ALLOW_SIGN_RSA_MD5;
	if (os_strstr(txt, "tls_disable_time_checks=1"))
		params->flags |= TLS_CONN_DISABLE_TIME_CHECKS;
	if (os_strstr(txt, "tls_disable_session_ticket=1"))
		params->flags |= TLS_CONN_DISABLE_SESSION_TICKET;
	if (os_strstr(txt, "tls_disable_session_ticket=0"))
		params->flags &= ~TLS_CONN_DISABLE_SESSION_TICKET;
}