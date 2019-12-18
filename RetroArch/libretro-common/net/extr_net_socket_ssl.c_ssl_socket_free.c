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
struct ssl_state {int /*<<< orphan*/  ca; int /*<<< orphan*/  entropy; int /*<<< orphan*/  ctr_drbg; int /*<<< orphan*/  conf; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ssl_state*) ; 
 int /*<<< orphan*/  mbedtls_ctr_drbg_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_entropy_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ssl_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ssl_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_x509_crt_free (int /*<<< orphan*/ *) ; 

void ssl_socket_free(void *state_data)
{
   struct ssl_state *state = (struct ssl_state*)state_data;

   if (!state)
      return;

   mbedtls_ssl_free(&state->ctx);
   mbedtls_ssl_config_free(&state->conf);
   mbedtls_ctr_drbg_free(&state->ctr_drbg);
   mbedtls_entropy_free(&state->entropy);
#if defined(MBEDTLS_X509_CRT_PARSE_C)
   mbedtls_x509_crt_free(&state->ca);
#endif

   free(state);
}