#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  iv; int /*<<< orphan*/  key; int /*<<< orphan*/  ipoly; int /*<<< orphan*/  ichacha; scalar_t__ seq; } ;
typedef  TYPE_1__ br_sslrec_chapol_context ;
typedef  int /*<<< orphan*/  br_poly1305_run ;
typedef  int /*<<< orphan*/  br_chacha20_run ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 

__attribute__((used)) static void
gen_chapol_init(br_sslrec_chapol_context *cc,
	br_chacha20_run ichacha, br_poly1305_run ipoly,
	const void *key, const void *iv)
{
	cc->seq = 0;
	cc->ichacha = ichacha;
	cc->ipoly = ipoly;
	memcpy(cc->key, key, sizeof cc->key);
	memcpy(cc->iv, iv, sizeof cc->iv);
}