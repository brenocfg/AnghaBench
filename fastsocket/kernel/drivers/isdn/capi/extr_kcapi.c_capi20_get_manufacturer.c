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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct capi_ctr {scalar_t__ cardstate; int /*<<< orphan*/  manu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPI_MANUFACTURER_LEN ; 
 int /*<<< orphan*/  CAPI_NOERROR ; 
 int /*<<< orphan*/  CAPI_REGNOTINSTALLED ; 
 scalar_t__ CARD_RUNNING ; 
 int /*<<< orphan*/  capi_manufakturer ; 
 struct capi_ctr* get_capi_ctr_by_nr (scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u16 capi20_get_manufacturer(u32 contr, u8 *buf)
{
	struct capi_ctr *card;

	if (contr == 0) {
		strlcpy(buf, capi_manufakturer, CAPI_MANUFACTURER_LEN);
		return CAPI_NOERROR;
	}
	card = get_capi_ctr_by_nr(contr);
	if (!card || card->cardstate != CARD_RUNNING) 
		return CAPI_REGNOTINSTALLED;
	strlcpy(buf, card->manu, CAPI_MANUFACTURER_LEN);
	return CAPI_NOERROR;
}