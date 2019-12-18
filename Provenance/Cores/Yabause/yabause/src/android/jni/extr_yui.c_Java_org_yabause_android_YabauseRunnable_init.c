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
struct TYPE_7__ {int sh2coretype; scalar_t__ skip_load; scalar_t__ frameskip; int /*<<< orphan*/  videoformattype; int /*<<< orphan*/  cartpath; int /*<<< orphan*/  mpegpath; int /*<<< orphan*/  buppath; int /*<<< orphan*/  cdpath; int /*<<< orphan*/  biospath; scalar_t__ regionid; int /*<<< orphan*/  carttype; int /*<<< orphan*/  cdcoretype; int /*<<< orphan*/  sndcoretype; int /*<<< orphan*/  vidcoretype; int /*<<< orphan*/  percoretype; int /*<<< orphan*/  m68kcoretype; } ;
typedef  TYPE_1__ yabauseinit_struct ;
typedef  int /*<<< orphan*/  jobject ;
typedef  int jint ;
struct TYPE_8__ {int /*<<< orphan*/  (* NewGlobalRef ) (TYPE_2__**,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  CDCORE_ISO ; 
 int /*<<< orphan*/  GetBiosPath () ; 
 int /*<<< orphan*/  GetCartridgePath () ; 
 int /*<<< orphan*/  GetCartridgeType () ; 
 int /*<<< orphan*/  GetGamePath () ; 
 int /*<<< orphan*/  GetMemoryPath () ; 
 int /*<<< orphan*/  M68KCORE_C68K ; 
 int /*<<< orphan*/  OSDCORE_SOFT ; 
 int /*<<< orphan*/  OSDChangeCore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERCORE_DUMMY ; 
 int /*<<< orphan*/  PERPAD_A ; 
 int /*<<< orphan*/  PERPAD_B ; 
 int /*<<< orphan*/  PERPAD_C ; 
 int /*<<< orphan*/  PERPAD_DOWN ; 
 int /*<<< orphan*/  PERPAD_LEFT ; 
 int /*<<< orphan*/  PERPAD_RIGHT ; 
 int /*<<< orphan*/  PERPAD_START ; 
 int /*<<< orphan*/  PERPAD_UP ; 
 int /*<<< orphan*/  PERPAD_X ; 
 int /*<<< orphan*/  PERPAD_Y ; 
 int /*<<< orphan*/  PERPAD_Z ; 
 int /*<<< orphan*/  PORTDATA1 ; 
 void* PerPadAdd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PerPortReset () ; 
 int /*<<< orphan*/  PerSetKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int SH2CORE_DEFAULT ; 
 int /*<<< orphan*/  SNDCORE_AUDIOTRACK ; 
 int /*<<< orphan*/  SNDCORE_OPENSL ; 
 int /*<<< orphan*/  ScspSetFrameAccurate (int) ; 
 int /*<<< orphan*/  VIDCORE_SOFT ; 
 int /*<<< orphan*/  VIDEOFORMATTYPE_NTSC ; 
 int YabauseInit (TYPE_1__*) ; 
 int initEGLFunc () ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpegpath ; 
 int /*<<< orphan*/  stub1 (TYPE_2__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yabause ; 

jint
Java_org_yabause_android_YabauseRunnable_init( JNIEnv* env, jobject obj, jobject yab )
{
    yabauseinit_struct yinit;
    int res;
    void * padbits;

    if( initEGLFunc() == -1 ) return -1;

    yabause = (*env)->NewGlobalRef(env, yab);

    memset(&yinit, 0, sizeof(yabauseinit_struct));

    yinit.m68kcoretype = M68KCORE_C68K;
    yinit.percoretype = PERCORE_DUMMY;
#ifdef SH2_DYNAREC
    yinit.sh2coretype = 2;
#else
    yinit.sh2coretype = SH2CORE_DEFAULT;
#endif
    yinit.vidcoretype = VIDCORE_SOFT;
#ifdef HAVE_OPENSL
    yinit.sndcoretype = SNDCORE_OPENSL;
#else
    yinit.sndcoretype = SNDCORE_AUDIOTRACK;
#endif
    yinit.cdcoretype = CDCORE_ISO;
    yinit.carttype = GetCartridgeType();
    yinit.regionid = 0;
    yinit.biospath = GetBiosPath();
    yinit.cdpath = GetGamePath();
    yinit.buppath = GetMemoryPath();
    yinit.mpegpath = mpegpath;
    yinit.cartpath = GetCartridgePath();
    yinit.videoformattype = VIDEOFORMATTYPE_NTSC;
    yinit.frameskip = 0;
    yinit.skip_load = 0;

    res = YabauseInit(&yinit);

    OSDChangeCore(OSDCORE_SOFT);

    PerPortReset();
    padbits = PerPadAdd(&PORTDATA1);
    PerSetKey(PERPAD_UP, PERPAD_UP, padbits);
    PerSetKey(PERPAD_RIGHT, PERPAD_RIGHT, padbits);
    PerSetKey(PERPAD_DOWN, PERPAD_DOWN, padbits);
    PerSetKey(PERPAD_LEFT, PERPAD_LEFT, padbits);
    PerSetKey(PERPAD_START, PERPAD_START, padbits);
    PerSetKey(PERPAD_A, PERPAD_A, padbits);
    PerSetKey(PERPAD_B, PERPAD_B, padbits);
    PerSetKey(PERPAD_C, PERPAD_C, padbits);
    PerSetKey(PERPAD_X, PERPAD_X, padbits);
    PerSetKey(PERPAD_Y, PERPAD_Y, padbits);
    PerSetKey(PERPAD_Z, PERPAD_Z, padbits);

    ScspSetFrameAccurate(1);

    return res;
}