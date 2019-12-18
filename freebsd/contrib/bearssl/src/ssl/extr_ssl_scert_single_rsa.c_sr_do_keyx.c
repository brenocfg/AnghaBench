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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  sk; int /*<<< orphan*/  irsacore; } ;
typedef  TYPE_1__ br_ssl_server_policy_rsa_context ;
typedef  int /*<<< orphan*/  br_ssl_server_policy_class ;

/* Variables and functions */
 int /*<<< orphan*/  br_rsa_ssl_decrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t) ; 

__attribute__((used)) static uint32_t
sr_do_keyx(const br_ssl_server_policy_class **pctx,
	unsigned char *data, size_t *len)
{
	br_ssl_server_policy_rsa_context *pc;

	pc = (br_ssl_server_policy_rsa_context *)pctx;
	return br_rsa_ssl_decrypt(pc->irsacore, pc->sk, data, *len);
}