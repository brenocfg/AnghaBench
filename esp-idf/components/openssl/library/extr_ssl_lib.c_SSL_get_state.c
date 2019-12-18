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
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  OSSL_HANDSHAKE_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_ASSERT1 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SSL_METHOD_CALL (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  get_state ; 

OSSL_HANDSHAKE_STATE SSL_get_state(const SSL *ssl)
{
    OSSL_HANDSHAKE_STATE state;

    SSL_ASSERT1(ssl);

    state = SSL_METHOD_CALL(get_state, ssl);

    return state;
}