#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  size_t s32 ;
typedef  int /*<<< orphan*/  s16 ;
struct TYPE_4__ {scalar_t__ (* GetAudioSpace ) () ;int /*<<< orphan*/  (* UpdateAudio ) (scalar_t__*,scalar_t__*,scalar_t__) ;} ;
struct TYPE_3__ {int scieb; int sample_timer; int /*<<< orphan*/  tcctl; int /*<<< orphan*/  timc; int /*<<< orphan*/  tbctl; int /*<<< orphan*/  timb; int /*<<< orphan*/  tactl; int /*<<< orphan*/  tima; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_AviSoundUpdate (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCSPLOG (char*,int) ; 
 int SCSP_INTERRUPT_TIMER_A ; 
 int SCSP_INTERRUPT_TIMER_B ; 
 int SCSP_INTERRUPT_TIMER_C ; 
 scalar_t__ SCSP_SOUND_BUFSIZE ; 
 TYPE_2__* SNDCore ; 
 int /*<<< orphan*/  ScspConvert32uto16s (size_t*,size_t*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ScspGenerateAudio (size_t*,size_t*,scalar_t__) ; 
 int /*<<< orphan*/  ScspRunM68K (scalar_t__) ; 
 int /*<<< orphan*/  ScspTimerCyclesLeft (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScspUpdateTimer (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ scsp ; 
 size_t* scsp_buffer_L ; 
 size_t* scsp_buffer_R ; 
 int /*<<< orphan*/  scsp_clock ; 
 scalar_t__ scsp_frame_accurate ; 
 scalar_t__ scsp_sound_genpos ; 
 scalar_t__ scsp_sound_left ; 
 scalar_t__ stub1 () ; 
 int /*<<< orphan*/  stub2 (scalar_t__*,scalar_t__*,scalar_t__) ; 
 scalar_t__ stub3 () ; 
 int /*<<< orphan*/  stub4 (scalar_t__*,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static void ScspDoExec(u32 cycles)
{
#if 0
   s16 stereodata16[(44100 / 60) * 16]; //11760
#endif
   u32 cycles_left;
   u32 sample_count;
   u32 audio_free;


   // If any of the timer interrupts are enabled, give the M68K a chance
   // to respond to them immediately, so that music doesn't slow down if
   // the SCSP thread gets behind and executes a lot of cycles at once.
   sample_count = 0;
   cycles_left = cycles;
   while (cycles_left > 0)
   {
      u32 this_samples = 0;
      u32 this_cycles = cycles_left;
      if (scsp.scieb & (1 << SCSP_INTERRUPT_TIMER_A))
         this_cycles = MIN(this_cycles, ScspTimerCyclesLeft(scsp.tima, scsp.tactl));
      if (scsp.scieb & (1 << SCSP_INTERRUPT_TIMER_B))
         this_cycles = MIN(this_cycles, ScspTimerCyclesLeft(scsp.timb, scsp.tbctl));
      if (scsp.scieb & (1 << SCSP_INTERRUPT_TIMER_C))
         this_cycles = MIN(this_cycles, ScspTimerCyclesLeft(scsp.timc, scsp.tcctl));

      scsp.sample_timer += this_cycles;
      this_samples = scsp.sample_timer >> 8;
      scsp.sample_timer &= 0xFF;
      cycles_left -= this_cycles;
      sample_count += this_samples;

      ScspRunM68K(this_cycles);

      ScspUpdateTimer(this_samples, &scsp.tima, scsp.tactl,
                      SCSP_INTERRUPT_TIMER_A);
      ScspUpdateTimer(this_samples, &scsp.timb, scsp.tbctl,
                      SCSP_INTERRUPT_TIMER_B);
      ScspUpdateTimer(this_samples, &scsp.timc, scsp.tcctl,
                      SCSP_INTERRUPT_TIMER_C);
   }

   if (scsp_frame_accurate)
   {
      s32 *bufL, *bufR;

      // Update sound buffers
      if (scsp_sound_left + sample_count > SCSP_SOUND_BUFSIZE)
      {
         u32 overrun = (scsp_sound_left + sample_count) - SCSP_SOUND_BUFSIZE;
         SCSPLOG("WARNING: Sound buffer overrun, %u samples\n", (int)overrun);
         scsp_sound_left -= overrun;
      }
      while (sample_count > 0)
      {
         u32 this_count = sample_count;
         if (scsp_sound_genpos >= SCSP_SOUND_BUFSIZE)
            scsp_sound_genpos = 0;
         if (this_count > SCSP_SOUND_BUFSIZE - scsp_sound_genpos)
            this_count = SCSP_SOUND_BUFSIZE - scsp_sound_genpos;
         bufL = &scsp_buffer_L[scsp_sound_genpos];
         bufR = &scsp_buffer_R[scsp_sound_genpos];
         ScspGenerateAudio(bufL, bufR, this_count);
         scsp_sound_genpos += this_count;
         scsp_sound_left += this_count;
         sample_count -= this_count;
      }

      // Send audio to the output device if possible
      while (scsp_sound_left > 0 && (audio_free = SNDCore->GetAudioSpace()) > 0)
      {
         s32 out_start = (s32)scsp_sound_genpos - (s32)scsp_sound_left;
         if (out_start < 0)
            out_start += SCSP_SOUND_BUFSIZE;
         if (audio_free > scsp_sound_left)
            audio_free = scsp_sound_left;
         if (audio_free > SCSP_SOUND_BUFSIZE - out_start)
            audio_free = SCSP_SOUND_BUFSIZE - out_start;
         SNDCore->UpdateAudio((u32 *)&scsp_buffer_L[out_start],
                              (u32 *)&scsp_buffer_R[out_start], audio_free);
         scsp_sound_left -= audio_free;
#if 0
         ScspConvert32uto16s(&scsp_buffer_L[out_start], &scsp_buffer_R[out_start], (s16 *)stereodata16, audio_free);
         DRV_AviSoundUpdate(stereodata16, audio_free);
#endif
      }
   }
   else  // !scsp_frame_accurate
   {
      if ((audio_free = SNDCore->GetAudioSpace()))
      {
         if (audio_free > SCSP_SOUND_BUFSIZE)
            audio_free = SCSP_SOUND_BUFSIZE;
         ScspGenerateAudio(scsp_buffer_L, scsp_buffer_R, audio_free);
         SNDCore->UpdateAudio((u32 *)scsp_buffer_L,
                              (u32 *)scsp_buffer_R, audio_free);
#if 0
         ScspConvert32uto16s((s32 *)scsp_buffer_L, (s32 *)scsp_buffer_R, (s16 *)stereodata16, audio_free);
         DRV_AviSoundUpdate(stereodata16, audio_free);
#endif
      }
   }  // if (scsp_frame_accurate)

   // Update scsp_clock last, so the main thread can use it as a signal
   // that we've finished processing to this point
   scsp_clock += cycles;
}