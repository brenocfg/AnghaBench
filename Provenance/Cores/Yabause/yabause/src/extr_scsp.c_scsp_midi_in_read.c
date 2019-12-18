#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int midflag; int midincnt; int* midinbuf; } ;

/* Variables and functions */
 int SCSP_MIDI_IN_EMP ; 
 int SCSP_MIDI_IN_FUL ; 
 int SCSP_MIDI_IN_OVF ; 
 TYPE_1__ scsp ; 
 int /*<<< orphan*/  scsp_main_interrupt (int) ; 
 int /*<<< orphan*/  scsp_sound_interrupt (int) ; 

u8
scsp_midi_in_read (void)
{
  u8 data;

  scsp.midflag &= ~(SCSP_MIDI_IN_OVF | SCSP_MIDI_IN_FUL);

  if (scsp.midincnt > 0)
    {
      if (scsp.midincnt > 1)
        {
          scsp_sound_interrupt(0x8);
          scsp_main_interrupt(0x8);
        }
      else
        {
          scsp.midflag |= SCSP_MIDI_IN_EMP;
        }

      data = scsp.midinbuf[0];

      switch ((--scsp.midincnt) & 3)
        {
        case 1:
          scsp.midinbuf[0] = scsp.midinbuf[1];
          break;

        case 2:
          scsp.midinbuf[0] = scsp.midinbuf[1];
          scsp.midinbuf[1] = scsp.midinbuf[2];
          break;

        case 3:
          scsp.midinbuf[0] = scsp.midinbuf[1];
          scsp.midinbuf[1] = scsp.midinbuf[2];
          scsp.midinbuf[2] = scsp.midinbuf[3];
          break;
        }

      return data;
    }

  return 0xFF;
}