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
typedef  int /*<<< orphan*/  uint8_t ;
struct ssl_state {int /*<<< orphan*/  ctx; int /*<<< orphan*/  net_ctx; } ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_WANT_READ ; 
 int MBEDTLS_ERR_SSL_WANT_WRITE ; 
 int /*<<< orphan*/  mbedtls_net_set_block (int /*<<< orphan*/ *) ; 
 int mbedtls_ssl_write (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

int ssl_socket_send_all_blocking(void *state_data, const void *data_, size_t size, bool no_signal)
{
   struct ssl_state *state = (struct ssl_state*)state_data;
   const uint8_t *data = (const uint8_t*)data_;
   int ret;

   mbedtls_net_set_block(&state->net_ctx);

   while ((ret = mbedtls_ssl_write(&state->ctx, data, size)) <= 0)
   {
      if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE)
         return false;
   }

   return true;
}