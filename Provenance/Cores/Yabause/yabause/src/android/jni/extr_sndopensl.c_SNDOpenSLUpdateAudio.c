#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  s16 ;
struct TYPE_3__ {scalar_t__ (* Enqueue ) (TYPE_1__**,scalar_t__,int) ;} ;
typedef  scalar_t__ SLresult ;

/* Variables and functions */
 int MAX_BUFFER_CNT ; 
 scalar_t__ SL_RESULT_SUCCESS ; 
 TYPE_1__** bqPlayerBufferQueue ; 
 size_t currentpos ; 
 int mbufferSizeInBytes ; 
 int /*<<< orphan*/  muted ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  push_index (size_t) ; 
 int /*<<< orphan*/  sdlConvert32uto16s (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int* soundoffset ; 
 scalar_t__* stereodata16 ; 
 scalar_t__ stub1 (TYPE_1__**,scalar_t__,int) ; 

__attribute__((used)) static void SNDOpenSLUpdateAudio(u32 *leftchanbuffer, u32 *rightchanbuffer, u32 num_samples)
{
//   return;


   u32 copy1size=0;
   int nextpos;

   copy1size = (num_samples * sizeof(s16) * 2);
   //printf("SNDOpenSLUpdateAudio %08X,%08X,%08X",currentpos,soundoffset[currentpos],copy1size);

   sdlConvert32uto16s((s32 *)leftchanbuffer, (s32 *)rightchanbuffer, (s16 *)(((u8 *)stereodata16[currentpos])+soundoffset[currentpos] ), copy1size / sizeof(s16) / 2);

   soundoffset[currentpos] += copy1size;
   
   if (soundoffset[currentpos] >= mbufferSizeInBytes) {

      if (!muted) {
         // here we only enqueue one buffer because it is a long clip,
         // but for streaming playback we would typically enqueue at least 2 buffers to start
         SLresult result;
         push_index(currentpos);
         result = (*bqPlayerBufferQueue)->Enqueue(bqPlayerBufferQueue, stereodata16[currentpos], soundoffset[currentpos]);
         if (SL_RESULT_SUCCESS != result) {
            printf("Fail to Add queue");
               return;
         }
      }
      nextpos = currentpos+1;
      if( nextpos >= MAX_BUFFER_CNT ) { nextpos = 0; }
      currentpos = nextpos;
      
   }
   
}