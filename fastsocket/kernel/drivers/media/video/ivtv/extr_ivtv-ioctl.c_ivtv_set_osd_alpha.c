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
struct ivtv {int /*<<< orphan*/  osd_chroma_key; int /*<<< orphan*/  osd_chroma_key_state; int /*<<< orphan*/  osd_local_alpha_state; int /*<<< orphan*/  osd_global_alpha; int /*<<< orphan*/  osd_global_alpha_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_OSD_SET_CHROMA_KEY ; 
 int /*<<< orphan*/  CX2341X_OSD_SET_GLOBAL_ALPHA ; 
 int /*<<< orphan*/  ivtv_vapi (struct ivtv*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

void ivtv_set_osd_alpha(struct ivtv *itv)
{
	ivtv_vapi(itv, CX2341X_OSD_SET_GLOBAL_ALPHA, 3,
		itv->osd_global_alpha_state, itv->osd_global_alpha, !itv->osd_local_alpha_state);
	ivtv_vapi(itv, CX2341X_OSD_SET_CHROMA_KEY, 2, itv->osd_chroma_key_state, itv->osd_chroma_key);
}