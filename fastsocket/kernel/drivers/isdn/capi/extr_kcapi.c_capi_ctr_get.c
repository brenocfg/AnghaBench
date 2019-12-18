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
struct capi_ctr {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct capi_ctr *
capi_ctr_get(struct capi_ctr *card)
{
	if (!try_module_get(card->owner))
		return NULL;
	return card;
}