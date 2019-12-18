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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct capi_version {int dummy; } ;
struct capi_ctr {scalar_t__ cardstate; int /*<<< orphan*/  version; } ;
typedef  int /*<<< orphan*/  capi_version ;

/* Variables and functions */
 int /*<<< orphan*/  CAPI_NOERROR ; 
 int /*<<< orphan*/  CAPI_REGNOTINSTALLED ; 
 scalar_t__ CARD_RUNNING ; 
 struct capi_version driver_version ; 
 struct capi_ctr* get_capi_ctr_by_nr (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 

u16 capi20_get_version(u32 contr, struct capi_version *verp)
{
	struct capi_ctr *card;

	if (contr == 0) {
		*verp = driver_version;
		return CAPI_NOERROR;
	}
	card = get_capi_ctr_by_nr(contr);
	if (!card || card->cardstate != CARD_RUNNING) 
		return CAPI_REGNOTINSTALLED;

	memcpy((void *) verp, &card->version, sizeof(capi_version));
	return CAPI_NOERROR;
}