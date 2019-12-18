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
struct cryptd_ahash {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_ahash (int /*<<< orphan*/ *) ; 

void cryptd_free_ahash(struct cryptd_ahash *tfm)
{
	crypto_free_ahash(&tfm->base);
}