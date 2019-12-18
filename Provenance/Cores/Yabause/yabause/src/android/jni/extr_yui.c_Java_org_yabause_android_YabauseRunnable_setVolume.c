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
typedef  int /*<<< orphan*/  jobject ;
typedef  scalar_t__ jint ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  SCSP_MUTE_USER ; 
 int /*<<< orphan*/  ScspMuteAudio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScspSetVolume (scalar_t__) ; 
 int /*<<< orphan*/  ScspUnMuteAudio (int /*<<< orphan*/ ) ; 

void
Java_org_yabause_android_YabauseRunnable_setVolume( JNIEnv* env, jobject obj, jint volume )
{
    if (0 == volume)
       ScspMuteAudio(SCSP_MUTE_USER);
    else {
       ScspUnMuteAudio(SCSP_MUTE_USER);
       ScspSetVolume(volume);
    }
}