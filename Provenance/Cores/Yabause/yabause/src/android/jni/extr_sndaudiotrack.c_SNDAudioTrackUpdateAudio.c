#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  s16 ;
typedef  scalar_t__ jbyteArray ;
struct TYPE_8__ {scalar_t__ (* GetEnv ) (TYPE_2__**,void**,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  (* CallNonvirtualIntMethod ) (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* SetByteArrayRegion ) (TYPE_1__**,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;scalar_t__ (* NewByteArray ) (TYPE_1__**,int) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 scalar_t__ JNI_OK ; 
 int /*<<< orphan*/  JNI_VERSION_1_6 ; 
 int /*<<< orphan*/  cAudioTrack ; 
 int /*<<< orphan*/  gtrack ; 
 int /*<<< orphan*/  mWrite ; 
 int mbufferSizeInBytes ; 
 int /*<<< orphan*/  muted ; 
 int /*<<< orphan*/  sdlConvert32uto16s (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int soundoffset ; 
 scalar_t__ stereodata16 ; 
 scalar_t__ stub1 (TYPE_2__**,void**,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_1__**,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__**,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 TYPE_2__** yvm ; 

__attribute__((used)) static void SNDAudioTrackUpdateAudio(u32 *leftchanbuffer, u32 *rightchanbuffer, u32 num_samples)
{
   u32 copy1size=0;

   copy1size = (num_samples * sizeof(s16) * 2);

   sdlConvert32uto16s((s32 *)leftchanbuffer, (s32 *)rightchanbuffer, (s16 *)(((u8 *)stereodata16)+soundoffset), copy1size / sizeof(s16) / 2);

   soundoffset += copy1size;

   if (soundoffset > mbufferSizeInBytes) {
      if (! muted) {
         JNIEnv * env;
         jbyteArray array;

         if ((*yvm)->GetEnv(yvm, (void**) &env, JNI_VERSION_1_6) != JNI_OK)
             return;

         array = (*env)->NewByteArray(env, soundoffset);
         if(array) {
            (*env)->SetByteArrayRegion(env, array, 0, soundoffset, (u8 *) stereodata16);
         }

         (*env)->CallNonvirtualIntMethod(env, gtrack, cAudioTrack, mWrite, array, 0, soundoffset);
      }

      soundoffset = 0;
   }
}