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
 int MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY ; 
 int MBEDTLS_ERR_SSL_WANT_READ ; 
 int MBEDTLS_ERR_SSL_WANT_WRITE ; 
 int /*<<< orphan*/  mbedtls_net_set_block (int /*<<< orphan*/ *) ; 
 int mbedtls_ssl_read (int /*<<< orphan*/ *,unsigned char*,size_t) ; 

int ssl_socket_receive_all_blocking(void *state_data, void *data_, size_t size)
{
   struct ssl_state *state = (struct ssl_state*)state_data;
   const uint8_t *data = (const uint8_t*)data_;

   mbedtls_net_set_block(&state->net_ctx);

   while (1)
   {
      /* mbedtls_ssl_read wants non-const data but it only reads it, so this cast is safe */
      int ret = mbedtls_ssl_read(&state->ctx, (unsigned char*)data, size);

      if (ret == MBEDTLS_ERR_SSL_WANT_READ || ret == MBEDTLS_ERR_SSL_WANT_WRITE)
         continue;

      if (ret == MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY)
         break;

      if (ret == 0)
         break; /* normal EOF */

      if (ret < 0)
         return -1;
   }

   return 1;
}