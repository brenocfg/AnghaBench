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
struct xfrm_state {struct esp_data* data; } ;
struct esp_data {int /*<<< orphan*/  aead; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_aead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct esp_data*) ; 

__attribute__((used)) static void esp6_destroy(struct xfrm_state *x)
{
	struct esp_data *esp = x->data;

	if (!esp)
		return;

	crypto_free_aead(esp->aead);
	kfree(esp);
}