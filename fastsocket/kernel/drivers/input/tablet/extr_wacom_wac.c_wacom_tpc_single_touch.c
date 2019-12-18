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
struct wacom_wac {char* data; TYPE_1__* shared; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int touch_down; int /*<<< orphan*/  stylus_in_proximity; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 size_t WACOM_PKGLEN_TPC1FG ; 
 int get_unaligned_le16 (char*) ; 
 int le16_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wacom_report_abs (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wacom_report_key (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wacom_tpc_single_touch(struct wacom_wac *wacom, void *wcombo, size_t len)
{
	char *data = wacom->data;
	bool prox;
	int x = 0, y = 0;

	if (!wacom->shared->stylus_in_proximity) {
		if (len == WACOM_PKGLEN_TPC1FG) {
			prox = data[0] & 0x01;
			x = get_unaligned_le16(&data[1]);
			y = get_unaligned_le16(&data[3]);
		} else { /* with capacity */
			prox = data[1] & 0x01;
			x = le16_to_cpup((__le16 *)&data[2]);
			y = le16_to_cpup((__le16 *)&data[4]);
		}
	} else
		/* force touch out when pen is in prox */
		prox = 0;

	if (prox) {
		wacom_report_abs(wcombo, ABS_X, x);
		wacom_report_abs(wcombo, ABS_Y, y);
	}
	wacom_report_key(wcombo, BTN_TOUCH, prox);

	/* keep touch state for pen events */
	wacom->shared->touch_down = prox;

	return 1;
}