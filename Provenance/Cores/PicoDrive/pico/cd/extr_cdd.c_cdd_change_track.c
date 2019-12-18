#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * cdda_stream; } ;
struct TYPE_6__ {TYPE_1__* tracks; } ;
struct TYPE_7__ {TYPE_2__ toc; } ;
struct TYPE_5__ {int offset; int start; int end; int /*<<< orphan*/ * fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_CD ; 
 TYPE_4__* Pico_mcd ; 
 TYPE_3__ cdd ; 
 int /*<<< orphan*/  cdda_start_play (int,int,int) ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 

__attribute__((used)) static void cdd_change_track(int index, int lba)
{
  int i, base, lba_offset, lb_len;

  for (i = index; i > 0; i--)
    if (cdd.toc.tracks[i].fd != NULL)
      break;

  Pico_mcd->cdda_stream = cdd.toc.tracks[i].fd;
  base = cdd.toc.tracks[index].offset;
  lba_offset = lba - cdd.toc.tracks[index].start;
  lb_len = cdd.toc.tracks[index].end - cdd.toc.tracks[index].start;

  elprintf(EL_CD, "play #%d lba %d base %d", index, lba, base);

  cdda_start_play(base, lba_offset, lb_len);
}