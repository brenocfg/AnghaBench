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
struct ivtv {int /*<<< orphan*/  capturing; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_ENC_MUTE_AUDIO ; 
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtv_vapi (struct ivtv*,int /*<<< orphan*/ ,int,int) ; 

void ivtv_mute(struct ivtv *itv)
{
	if (atomic_read(&itv->capturing))
		ivtv_vapi(itv, CX2341X_ENC_MUTE_AUDIO, 1, 1);
	IVTV_DEBUG_INFO("Mute\n");
}