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
typedef  int /*<<< orphan*/  vrfy_buf ;
struct TYPE_2__ {int fd; } ;
struct ssl_state {TYPE_1__ net_ctx; int /*<<< orphan*/  ctx; int /*<<< orphan*/  domain; int /*<<< orphan*/  conf; int /*<<< orphan*/  ctr_drbg; int /*<<< orphan*/  ca; } ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_WANT_READ ; 
 int MBEDTLS_ERR_SSL_WANT_WRITE ; 
 int /*<<< orphan*/  MBEDTLS_SSL_IS_CLIENT ; 
 int /*<<< orphan*/  MBEDTLS_SSL_PRESET_DEFAULT ; 
 int /*<<< orphan*/  MBEDTLS_SSL_TRANSPORT_STREAM ; 
 int /*<<< orphan*/  MBEDTLS_SSL_VERIFY_OPTIONAL ; 
 int /*<<< orphan*/  mbedtls_ctr_drbg_random ; 
 int /*<<< orphan*/  mbedtls_net_recv ; 
 int /*<<< orphan*/  mbedtls_net_send ; 
 int /*<<< orphan*/  mbedtls_ssl_conf_authmode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_ssl_conf_ca_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ssl_conf_dbg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_ssl_conf_rng (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_ssl_config_defaults (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mbedtls_ssl_get_verify_result (int /*<<< orphan*/ *) ; 
 int mbedtls_ssl_handshake (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ssl_set_bio (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_ssl_set_hostname (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mbedtls_ssl_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_x509_crt_verify_info (char*,int,char*,int) ; 
 scalar_t__ socket_connect (int,void*,int) ; 
 int /*<<< orphan*/  ssl_debug ; 
 int /*<<< orphan*/  stderr ; 

int ssl_socket_connect(void *state_data, void *data, bool timeout_enable, bool nonblock)
{
   struct ssl_state *state = (struct ssl_state*)state_data;
   int ret, flags;

   if (socket_connect(state->net_ctx.fd, data, timeout_enable))
      return -1;

   if (mbedtls_ssl_config_defaults(&state->conf,
               MBEDTLS_SSL_IS_CLIENT,
               MBEDTLS_SSL_TRANSPORT_STREAM,
               MBEDTLS_SSL_PRESET_DEFAULT) != 0)
      return -1;

   mbedtls_ssl_conf_authmode(&state->conf, MBEDTLS_SSL_VERIFY_OPTIONAL);
   mbedtls_ssl_conf_ca_chain(&state->conf, &state->ca, NULL);
   mbedtls_ssl_conf_rng(&state->conf, mbedtls_ctr_drbg_random, &state->ctr_drbg);
   mbedtls_ssl_conf_dbg(&state->conf, ssl_debug, stderr);

   if (mbedtls_ssl_setup(&state->ctx, &state->conf) != 0)
      return -1;

#if defined(MBEDTLS_X509_CRT_PARSE_C)
   if (mbedtls_ssl_set_hostname(&state->ctx, state->domain) != 0)
      return -1;
#endif

   mbedtls_ssl_set_bio(&state->ctx, &state->net_ctx, mbedtls_net_send, mbedtls_net_recv, NULL);

   while ((ret = mbedtls_ssl_handshake(&state->ctx)) != 0)
   {
      if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE)
         return -1;
   }

   if ((flags = mbedtls_ssl_get_verify_result(&state->ctx)) != 0)
   {
      char vrfy_buf[512];
      mbedtls_x509_crt_verify_info(vrfy_buf, sizeof(vrfy_buf), "  ! ", flags);
   }

   return state->net_ctx.fd;
}