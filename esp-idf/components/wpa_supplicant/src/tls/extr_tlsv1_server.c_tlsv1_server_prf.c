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
struct TYPE_2__ {int /*<<< orphan*/  tls_version; } ;
struct tlsv1_server {scalar_t__ state; int /*<<< orphan*/  master_secret; TYPE_1__ rl; int /*<<< orphan*/  server_random; int /*<<< orphan*/  client_random; } ;

/* Variables and functions */
 scalar_t__ ESTABLISHED ; 
 int /*<<< orphan*/  TLS_MASTER_SECRET_LEN ; 
 int TLS_RANDOM_LEN ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int tls_prf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t) ; 

int tlsv1_server_prf(struct tlsv1_server *conn, const char *label,
		     int server_random_first, u8 *out, size_t out_len)
{
	u8 seed[2 * TLS_RANDOM_LEN];

	if (conn->state != ESTABLISHED)
		return -1;

	if (server_random_first) {
		os_memcpy(seed, conn->server_random, TLS_RANDOM_LEN);
		os_memcpy(seed + TLS_RANDOM_LEN, conn->client_random,
			  TLS_RANDOM_LEN);
	} else {
		os_memcpy(seed, conn->client_random, TLS_RANDOM_LEN);
		os_memcpy(seed + TLS_RANDOM_LEN, conn->server_random,
			  TLS_RANDOM_LEN);
	}

	return tls_prf(conn->rl.tls_version,
		       conn->master_secret, TLS_MASTER_SECRET_LEN,
		       label, seed, 2 * TLS_RANDOM_LEN, out, out_len);
}