#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/ * jobject ;
typedef  int /*<<< orphan*/ * jmethodID ;
typedef  int /*<<< orphan*/ * jclass ;
struct TYPE_15__ {scalar_t__ (* GetEnv ) (TYPE_2__**,void**,int /*<<< orphan*/ ) ;} ;
struct TYPE_14__ {int (* CallStaticIntMethod ) (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ;int /*<<< orphan*/  (* CallNonvirtualVoidMethod ) (TYPE_1__**,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;scalar_t__ (* NewGlobalRef ) (TYPE_1__**,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* NewObject ) (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int,int) ;int /*<<< orphan*/ * (* GetStaticMethodID ) (TYPE_1__**,int /*<<< orphan*/ *,char*,char*) ;int /*<<< orphan*/ * (* GetMethodID ) (TYPE_1__**,int /*<<< orphan*/ *,char*,char*) ;int /*<<< orphan*/ * (* FindClass ) (TYPE_1__**,char*) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 scalar_t__ JNI_OK ; 
 int /*<<< orphan*/  JNI_VERSION_1_6 ; 
 int /*<<< orphan*/ * cAudioTrack ; 
 scalar_t__ gtrack ; 
 int /*<<< orphan*/ * mWrite ; 
 scalar_t__ malloc (int) ; 
 int mbufferSizeInBytes ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ muted ; 
 int soundbufsize ; 
 int soundmaxvolume ; 
 scalar_t__ soundoffset ; 
 int soundvolume ; 
 int /*<<< orphan*/ * stereodata16 ; 
 scalar_t__ stub1 (TYPE_2__**,void**,int /*<<< orphan*/ ) ; 
 scalar_t__ stub10 (TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub11 (TYPE_1__**,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub2 (TYPE_1__**,char*) ; 
 scalar_t__ stub3 (TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub4 (TYPE_1__**,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * stub5 (TYPE_1__**,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * stub6 (TYPE_1__**,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * stub7 (TYPE_1__**,int /*<<< orphan*/ *,char*,char*) ; 
 int stub8 (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/ * stub9 (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int,int) ; 
 TYPE_2__** yvm ; 

__attribute__((used)) static int SNDAudioTrackInit(void)
{
   int sampleRateInHz = 44100;
   int channelConfig = 12; //AudioFormat.CHANNEL_OUT_STEREO
   int audioFormat = 2; //AudioFormat.ENCODING_PCM_16BIT
   JNIEnv * env;
   jobject mtrack = NULL;
   jmethodID mPlay = NULL;
   jmethodID mGetMinBufferSize = NULL;
   jmethodID mAudioTrack = NULL;

   if ((*yvm)->GetEnv(yvm, (void**) &env, JNI_VERSION_1_6) != JNI_OK)
       return -1;

   cAudioTrack = (*env)->FindClass(env, "android/media/AudioTrack");
   cAudioTrack = (jclass) (*env)->NewGlobalRef(env, cAudioTrack);

   mAudioTrack = (*env)->GetMethodID(env, cAudioTrack, "<init>", "(IIIIII)V");

   mWrite = (*env)->GetMethodID(env, cAudioTrack, "write", "([BII)I");

   mPlay = (*env)->GetMethodID(env, cAudioTrack, "play", "()V");

   mGetMinBufferSize = (*env)->GetStaticMethodID(env, cAudioTrack, "getMinBufferSize", "(III)I");

   mbufferSizeInBytes = (*env)->CallStaticIntMethod(env, cAudioTrack, mGetMinBufferSize, sampleRateInHz, channelConfig, audioFormat);

   mtrack = (*env)->NewObject(env, cAudioTrack, mAudioTrack, 3 /* STREAM_MUSIC */, sampleRateInHz, channelConfig, audioFormat, mbufferSizeInBytes, 1 /* MODE_STREAM */);

   gtrack = (*env)->NewGlobalRef(env, mtrack);

   (*env)->CallNonvirtualVoidMethod(env, gtrack, cAudioTrack, mPlay);

   if ((stereodata16 = (u16 *)malloc(2 * mbufferSizeInBytes)) == NULL)
      return -1;
   memset(stereodata16, 0, soundbufsize);

   soundvolume = 100;
   soundmaxvolume = 100;
   soundbufsize = 85;
   soundoffset = 0;
   muted = 0;

   return 0;
}