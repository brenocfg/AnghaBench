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
struct TYPE_2__ {scalar_t__ cdda_type; int /*<<< orphan*/  cdda_stream; } ;

/* Variables and functions */
 scalar_t__ CT_MP3 ; 
 scalar_t__ CT_WAV ; 
 TYPE_1__* Pico_mcd ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  mp3_start_play (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void cdda_start_play(int lba_base, int lba_offset, int lb_len)
{
  if (Pico_mcd->cdda_type == CT_MP3)
  {
    int pos1024 = 0;

    if (lba_offset)
      pos1024 = lba_offset * 1024 / lb_len;

    mp3_start_play(Pico_mcd->cdda_stream, pos1024);
    return;
  }

  pm_seek(Pico_mcd->cdda_stream, (lba_base + lba_offset) * 2352, SEEK_SET);
  if (Pico_mcd->cdda_type == CT_WAV)
  {
    // skip headers, assume it's 44kHz stereo uncompressed
    pm_seek(Pico_mcd->cdda_stream, 44, SEEK_CUR);
  }
}