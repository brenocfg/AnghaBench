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
typedef  int u32 ;
struct ivtv {scalar_t__ has_cx23415; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_DEC_GET_VERSION ; 
 int /*<<< orphan*/  CX2341X_ENC_GET_VERSION ; 
 int CX2341X_MBOX_MAX_DATA ; 
 int /*<<< orphan*/  IVTV_INFO (char*,int) ; 
 int /*<<< orphan*/  IVTV_WARN (char*) ; 
 int /*<<< orphan*/  ivtv_vapi_result (struct ivtv*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ivtv_firmware_versions(struct ivtv *itv)
{
	u32 data[CX2341X_MBOX_MAX_DATA];

	/* Encoder */
	ivtv_vapi_result(itv, data, CX2341X_ENC_GET_VERSION, 0);
	IVTV_INFO("Encoder revision: 0x%08x\n", data[0]);

	if (data[0] != 0x02060039)
		IVTV_WARN("Recommended firmware version is 0x02060039.\n");

	if (itv->has_cx23415) {
		/* Decoder */
		ivtv_vapi_result(itv, data, CX2341X_DEC_GET_VERSION, 0);
		IVTV_INFO("Decoder revision: 0x%08x\n", data[0]);
	}
}