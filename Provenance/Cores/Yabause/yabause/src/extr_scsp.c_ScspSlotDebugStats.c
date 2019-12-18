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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_4__ {TYPE_1__* slot; } ;
struct TYPE_3__ {int ssctl; int sbctl; int lpctl; scalar_t__ krs; int /*<<< orphan*/  mdy; int /*<<< orphan*/  mdx; int /*<<< orphan*/  mdl; scalar_t__ tl; scalar_t__ sdir; scalar_t__ swe; scalar_t__ rr; scalar_t__ lslnk; scalar_t__ ar; scalar_t__ eghold; scalar_t__ sr; scalar_t__ dr; scalar_t__ lea; scalar_t__ lsa; scalar_t__ sa; scalar_t__ pcm8b; } ;

/* Variables and functions */
 char* AddSoundLFO (char*,char*,int,int) ; 
 char* AddSoundLevel (char*,int) ; 
 char* AddSoundPan (char*,int) ; 
 int /*<<< orphan*/  AddString (char*,char*,...) ; 
 unsigned long SCSP_FREQ_LB ; 
 TYPE_2__ scsp ; 
 int scsp_r_w (int) ; 

void
ScspSlotDebugStats (u8 slotnum, char *outstring)
{
  u32 slotoffset = slotnum * 0x20;

  AddString (outstring, "Sound Source = ");
  switch (scsp.slot[slotnum].ssctl)
    {
    case 0:
      AddString (outstring, "External DRAM data\r\n");
      break;
    case 1:
      AddString (outstring, "Internal(Noise)\r\n");
      break;
    case 2:
      AddString (outstring, "Internal(0's)\r\n");
      break;
    default:
      AddString (outstring, "Invalid setting\r\n");
      break;
    }

  AddString (outstring, "Source bit = ");
  switch(scsp.slot[slotnum].sbctl)
    {
    case 0:
      AddString (outstring, "No bit reversal\r\n");
      break;
    case 1:
      AddString (outstring, "Reverse other bits\r\n");
      break;
    case 2:
      AddString (outstring, "Reverse sign bit\r\n");
      break;
    case 3:
      AddString (outstring, "Reverse sign and other bits\r\n");
      break;
    }

  // Loop Control
  AddString (outstring, "Loop Mode = ");
  switch (scsp.slot[slotnum].lpctl)
    {
    case 0:
      AddString (outstring, "Off\r\n");
      break;
    case 1:
      AddString (outstring, "Normal\r\n");
      break;
    case 2:
      AddString (outstring, "Reverse\r\n");
      break;
    case 3:
      AddString (outstring, "Alternating\r\n");
      break;
    }

  // PCM8B
  // NOTE: Need curly braces here, as AddString is a macro.
  if (scsp.slot[slotnum].pcm8b)
    {
      AddString (outstring, "8-bit samples\r\n");
    }
  else
    {
      AddString (outstring, "16-bit samples\r\n");
    }

  AddString (outstring, "Start Address = %05lX\r\n", (unsigned long)scsp.slot[slotnum].sa);
  AddString (outstring, "Loop Start Address = %04lX\r\n", (unsigned long)scsp.slot[slotnum].lsa >> SCSP_FREQ_LB);
  AddString (outstring, "Loop End Address = %04lX\r\n", (unsigned long)scsp.slot[slotnum].lea >> SCSP_FREQ_LB);
  AddString (outstring, "Decay 1 Rate = %ld\r\n", (unsigned long)scsp.slot[slotnum].dr);
  AddString (outstring, "Decay 2 Rate = %ld\r\n", (unsigned long)scsp.slot[slotnum].sr);
  if (scsp.slot[slotnum].eghold)
    AddString (outstring, "EG Hold Enabled\r\n");
  AddString (outstring, "Attack Rate = %ld\r\n", (unsigned long)scsp.slot[slotnum].ar);

  if (scsp.slot[slotnum].lslnk)
    AddString (outstring, "Loop Start Link Enabled\r\n");

  if (scsp.slot[slotnum].krs != 0)
    AddString (outstring, "Key rate scaling = %ld\r\n", (unsigned long)scsp.slot[slotnum].krs);

  AddString (outstring, "Decay Level = %d\r\n", (scsp_r_w(slotoffset + 0xA) >> 5) & 0x1F);
  AddString (outstring, "Release Rate = %ld\r\n", (unsigned long)scsp.slot[slotnum].rr);

  if (scsp.slot[slotnum].swe)
    AddString (outstring, "Stack Write Inhibited\r\n");

  if (scsp.slot[slotnum].sdir)
    AddString (outstring, "Sound Direct Enabled\r\n");

  AddString (outstring, "Total Level = %ld\r\n", (unsigned long)scsp.slot[slotnum].tl);

  AddString (outstring, "Modulation Level = %d\r\n", scsp.slot[slotnum].mdl);
  AddString (outstring, "Modulation Input X = %d\r\n", scsp.slot[slotnum].mdx);
  AddString (outstring, "Modulation Input Y = %d\r\n", scsp.slot[slotnum].mdy);

  AddString (outstring, "Octave = %d\r\n", (scsp_r_w(slotoffset + 0x10) >> 11) & 0xF);
  AddString (outstring, "Frequency Number Switch = %d\r\n", scsp_r_w(slotoffset + 0x10) & 0x3FF);

  AddString (outstring, "LFO Reset = %s\r\n", ((scsp_r_w(slotoffset + 0x12) >> 15) & 0x1) ? "TRUE" : "FALSE");
  AddString (outstring, "LFO Frequency = %d\r\n", (scsp_r_w(slotoffset + 0x12) >> 10) & 0x1F);
  outstring = AddSoundLFO (outstring, "LFO Frequency modulation waveform = ",
                           (scsp_r_w(slotoffset + 0x12) >> 5) & 0x7,
                           (scsp_r_w(slotoffset + 0x12) >> 8) & 0x3);
  AddString (outstring, "LFO Frequency modulation level = %d\r\n", (scsp_r_w(slotoffset + 0x12) >> 5) & 0x7);
  outstring = AddSoundLFO (outstring, "LFO Amplitude modulation waveform = ",
                           scsp_r_w(slotoffset + 0x12) & 0x7,
                           (scsp_r_w(slotoffset + 0x12) >> 3) & 0x3);
  AddString (outstring, "LFO Amplitude modulation level = %d\r\n", scsp_r_w(slotoffset + 0x12) & 0x7);

  AddString (outstring, "Input mix level = ");
  outstring = AddSoundLevel (outstring, scsp_r_w(slotoffset + 0x14) & 0x7);
  AddString (outstring, "Input Select = %d\r\n", (scsp_r_w(slotoffset + 0x14) >> 3) & 0x1F);

  AddString (outstring, "Direct data send level = ");
  outstring = AddSoundLevel (outstring, (scsp_r_w(slotoffset + 0x16) >> 13) & 0x7);
  AddString (outstring, "Direct data panpot = ");
  outstring = AddSoundPan (outstring, (scsp_r_w(slotoffset + 0x16) >> 8) & 0x1F);

  AddString (outstring, "Effect data send level = ");
  outstring = AddSoundLevel (outstring, (scsp_r_w(slotoffset + 0x16) >> 5) & 0x7);
  AddString (outstring, "Effect data panpot = ");
  outstring = AddSoundPan (outstring, scsp_r_w(slotoffset + 0x16) & 0x1F);
}