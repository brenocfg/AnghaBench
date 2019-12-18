#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_48__   TYPE_7__ ;
typedef  struct TYPE_47__   TYPE_6__ ;
typedef  struct TYPE_46__   TYPE_5__ ;
typedef  struct TYPE_45__   TYPE_4__ ;
typedef  struct TYPE_44__   TYPE_3__ ;
typedef  struct TYPE_43__   TYPE_2__ ;
typedef  struct TYPE_42__   TYPE_1__ ;
typedef  struct TYPE_41__   TYPE_19__ ;
typedef  struct TYPE_40__   TYPE_16__ ;
typedef  struct TYPE_39__   TYPE_12__ ;

/* Type definitions */
struct TYPE_48__ {scalar_t__ (* Realize ) (TYPE_7__**,int /*<<< orphan*/  const) ;scalar_t__ (* GetInterface ) (TYPE_7__**,int /*<<< orphan*/  const,TYPE_6__***) ;} ;
struct TYPE_47__ {scalar_t__ (* RegisterCallback ) (TYPE_6__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ (* SetPlayState ) (TYPE_6__**,int /*<<< orphan*/ ) ;} ;
struct TYPE_46__ {int member_1; int member_5; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_0; } ;
struct TYPE_45__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_44__ {TYPE_16__** member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_43__ {int /*<<< orphan*/ * member_1; TYPE_3__* member_0; } ;
struct TYPE_42__ {TYPE_5__* member_1; TYPE_4__* member_0; } ;
struct TYPE_41__ {scalar_t__ (* Realize ) (TYPE_19__**,int /*<<< orphan*/  const) ;scalar_t__ (* GetInterface ) (TYPE_19__**,int /*<<< orphan*/ ,TYPE_12__***) ;} ;
struct TYPE_40__ {scalar_t__ (* Realize ) (TYPE_16__**,int /*<<< orphan*/  const) ;} ;
struct TYPE_39__ {scalar_t__ (* CreateOutputMix ) (TYPE_12__**,TYPE_16__***,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ;scalar_t__ (* CreateAudioPlayer ) (TYPE_12__**,TYPE_7__***,TYPE_1__*,TYPE_2__*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ;} ;
typedef  scalar_t__ SLresult ;
typedef  int /*<<< orphan*/  SLboolean ;
typedef  int /*<<< orphan*/  SLInterfaceID ;
typedef  TYPE_1__ SLDataSource ;
typedef  TYPE_2__ SLDataSink ;
typedef  TYPE_3__ SLDataLocator_OutputMix ;
typedef  TYPE_4__ SLDataLocator_AndroidSimpleBufferQueue ;
typedef  TYPE_5__ SLDataFormat_PCM ;

/* Variables and functions */
 int /*<<< orphan*/  InitSoundBuff () ; 
 int /*<<< orphan*/  const SL_BOOLEAN_FALSE ; 
 int /*<<< orphan*/  const SL_BOOLEAN_TRUE ; 
 int /*<<< orphan*/  SL_BYTEORDER_LITTLEENDIAN ; 
 int /*<<< orphan*/  SL_DATAFORMAT_PCM ; 
 int /*<<< orphan*/  SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE ; 
 int /*<<< orphan*/  SL_DATALOCATOR_OUTPUTMIX ; 
 int /*<<< orphan*/  const SL_IID_BUFFERQUEUE ; 
 int /*<<< orphan*/  const SL_IID_EFFECTSEND ; 
 int /*<<< orphan*/  SL_IID_ENGINE ; 
 int /*<<< orphan*/  const SL_IID_ENVIRONMENTALREVERB ; 
 int /*<<< orphan*/  const SL_IID_MUTESOLO ; 
 int /*<<< orphan*/  const SL_IID_PLAY ; 
 int /*<<< orphan*/  const SL_IID_VOLUME ; 
 int /*<<< orphan*/  SL_PCMSAMPLEFORMAT_FIXED_16 ; 
 int /*<<< orphan*/  SL_PLAYSTATE_PLAYING ; 
 scalar_t__ SL_RESULT_SUCCESS ; 
 int /*<<< orphan*/  SL_SAMPLINGRATE_44_1 ; 
 int SL_SPEAKER_FRONT_LEFT ; 
 int SL_SPEAKER_FRONT_RIGHT ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_6__** bqPlayerBufferQueue ; 
 int /*<<< orphan*/  bqPlayerCallback ; 
 TYPE_6__** bqPlayerEffectSend ; 
 TYPE_6__** bqPlayerMuteSolo ; 
 TYPE_7__** bqPlayerObject ; 
 TYPE_6__** bqPlayerPlay ; 
 TYPE_6__** bqPlayerVolume ; 
 TYPE_12__** engineEngine ; 
 TYPE_19__** engineObject ; 
 scalar_t__ muted ; 
 TYPE_16__** outputMixObject ; 
 scalar_t__ slCreateEngine (TYPE_19__***,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_19__**,int /*<<< orphan*/  const) ; 
 scalar_t__ stub10 (TYPE_7__**,int /*<<< orphan*/  const,TYPE_6__***) ; 
 scalar_t__ stub11 (TYPE_7__**,int /*<<< orphan*/  const,TYPE_6__***) ; 
 scalar_t__ stub12 (TYPE_7__**,int /*<<< orphan*/  const,TYPE_6__***) ; 
 scalar_t__ stub13 (TYPE_6__**,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_19__**,int /*<<< orphan*/ ,TYPE_12__***) ; 
 scalar_t__ stub3 (TYPE_12__**,TYPE_16__***,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ stub4 (TYPE_16__**,int /*<<< orphan*/  const) ; 
 scalar_t__ stub5 (TYPE_12__**,TYPE_7__***,TYPE_1__*,TYPE_2__*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ stub6 (TYPE_7__**,int /*<<< orphan*/  const) ; 
 scalar_t__ stub7 (TYPE_7__**,int /*<<< orphan*/  const,TYPE_6__***) ; 
 scalar_t__ stub8 (TYPE_7__**,int /*<<< orphan*/  const,TYPE_6__***) ; 
 scalar_t__ stub9 (TYPE_6__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int SNDOpenSLInit(void)
{
   int i;
   
    // configure audio source
    SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
    SLDataFormat_PCM format_pcm = {SL_DATAFORMAT_PCM, 2, SL_SAMPLINGRATE_44_1,
        SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16,
        (SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT), SL_BYTEORDER_LITTLEENDIAN};
    SLDataSource audioSrc = {&loc_bufq, &format_pcm};
   
   SLresult result;
   

   // create engine
   result = slCreateEngine(&engineObject, 0, NULL, 0, NULL, NULL);
   assert(SL_RESULT_SUCCESS == result);

   // realize the engine
   result = (*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
   assert(SL_RESULT_SUCCESS == result);

   // get the engine interface, which is needed in order to create other objects
   result = (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engineEngine);
   assert(SL_RESULT_SUCCESS == result);

   // create output mix, with environmental reverb specified as a non-required interface
   const SLInterfaceID ids[1] = {SL_IID_ENVIRONMENTALREVERB};
   const SLboolean req[1] = {SL_BOOLEAN_FALSE};
 
   result = (*engineEngine)->CreateOutputMix(engineEngine, &outputMixObject, 1, ids, req);
   assert(SL_RESULT_SUCCESS == result);

   // realize the output mix
   result = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
   assert(SL_RESULT_SUCCESS == result);

    // configure audio sink
    SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObject};
    SLDataSink audioSnk = {&loc_outmix, NULL};

    // create audio player
    const SLInterfaceID aids[3] = {SL_IID_BUFFERQUEUE, SL_IID_EFFECTSEND, /*SL_IID_MUTESOLO,*/ SL_IID_VOLUME};
    const SLboolean areq[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE,/*SL_BOOLEAN_TRUE,*/ SL_BOOLEAN_TRUE};
    result = (*engineEngine)->CreateAudioPlayer(engineEngine, &bqPlayerObject, &audioSrc, &audioSnk,
            3, aids, areq);
    assert(SL_RESULT_SUCCESS == result);

    // realize the player
    result = (*bqPlayerObject)->Realize(bqPlayerObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);

    // get the play interface
    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_PLAY, &bqPlayerPlay);
    assert(SL_RESULT_SUCCESS == result);

    // get the buffer queue interface
    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_BUFFERQUEUE,
            &bqPlayerBufferQueue);
    assert(SL_RESULT_SUCCESS == result);

    // register callback on the buffer queue
    result = (*bqPlayerBufferQueue)->RegisterCallback(bqPlayerBufferQueue, bqPlayerCallback, NULL);
    assert(SL_RESULT_SUCCESS == result);

    // get the effect send interface
    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_EFFECTSEND,
            &bqPlayerEffectSend);
    assert(SL_RESULT_SUCCESS == result);

#if 0   // mute/solo is not supported for sources that are known to be mono, as this is
    // get the mute/solo interface
    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_MUTESOLO, &bqPlayerMuteSolo);
    assert(SL_RESULT_SUCCESS == result);
#endif

    // get the volume interface
    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_VOLUME, &bqPlayerVolume);
    assert(SL_RESULT_SUCCESS == result);

    InitSoundBuff();
      
   
   // set the player's state to playing
   result = (*bqPlayerPlay)->SetPlayState(bqPlayerPlay, SL_PLAYSTATE_PLAYING);
   assert(SL_RESULT_SUCCESS == result);

   muted = 0;

   return 0;
}