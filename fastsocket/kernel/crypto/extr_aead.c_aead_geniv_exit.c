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
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct crypto_tfm {TYPE_1__ crt_aead; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_aead (int /*<<< orphan*/ ) ; 

void aead_geniv_exit(struct crypto_tfm *tfm)
{
	crypto_free_aead(tfm->crt_aead.base);
}