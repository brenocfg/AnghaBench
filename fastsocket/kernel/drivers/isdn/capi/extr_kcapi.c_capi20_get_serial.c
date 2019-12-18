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
typedef  void u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct capi_ctr {scalar_t__ cardstate; int /*<<< orphan*/  serial; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPI_NOERROR ; 
 int /*<<< orphan*/  CAPI_REGNOTINSTALLED ; 
 int /*<<< orphan*/  CAPI_SERIAL_LEN ; 
 scalar_t__ CARD_RUNNING ; 
 int /*<<< orphan*/  driver_serial ; 
 struct capi_ctr* get_capi_ctr_by_nr (scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u16 capi20_get_serial(u32 contr, u8 *serial)
{
	struct capi_ctr *card;

	if (contr == 0) {
		strlcpy(serial, driver_serial, CAPI_SERIAL_LEN);
		return CAPI_NOERROR;
	}
	card = get_capi_ctr_by_nr(contr);
	if (!card || card->cardstate != CARD_RUNNING) 
		return CAPI_REGNOTINSTALLED;

	strlcpy((void *) serial, card->serial, CAPI_SERIAL_LEN);
	return CAPI_NOERROR;
}