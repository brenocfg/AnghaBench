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
struct secasvar {int flags; int /*<<< orphan*/ * sched; } ;
struct esp_algorithm {int ivlenval; } ;
typedef  TYPE_1__* esp_chachapoly_ctx_t ;
struct TYPE_2__ {scalar_t__ ccp_implicit_iv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_CHECK_ARG (struct esp_algorithm const*) ; 
 int SADB_X_EXT_IIV ; 

int
esp_chachapoly_ivlen(const struct esp_algorithm *algo,
					 struct secasvar *sav)
{
	ESP_CHECK_ARG(algo);

	if (sav != NULL &&
		((sav->sched != NULL && ((esp_chachapoly_ctx_t)sav->sched)->ccp_implicit_iv) ||
		 ((sav->flags & SADB_X_EXT_IIV) != 0))) {
		return 0;
	} else {
		return algo->ivlenval;
	}
}