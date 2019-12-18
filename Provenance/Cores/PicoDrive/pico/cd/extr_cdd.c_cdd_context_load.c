#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_7__ {TYPE_1__* tracks; } ;
struct TYPE_9__ {size_t index; size_t cycles; size_t latency; size_t lba; size_t scanOffset; size_t volume; size_t status; int sectorSize; TYPE_2__ toc; } ;
struct TYPE_8__ {scalar_t__ seekable; scalar_t__ datasource; } ;
struct TYPE_6__ {int start; scalar_t__ offset; scalar_t__ fd; TYPE_3__ vf; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_5__ cdd ; 
 int /*<<< orphan*/  cdd_change_track (size_t,int) ; 
 int /*<<< orphan*/  fseek (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_param (size_t*,int) ; 
 int /*<<< orphan*/  ogg_free (size_t) ; 
 int /*<<< orphan*/  ov_open (scalar_t__,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ov_pcm_seek (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  pm_seek (scalar_t__,int,int /*<<< orphan*/ ) ; 

int cdd_context_load(uint8 *state)
{
  int lba;
  int bufferptr = 0;

#ifdef USE_LIBTREMOR
#ifdef DISABLE_MANY_OGG_OPEN_FILES
  /* close previous track VORBIS file structure to save memory */
  if (cdd.toc.tracks[cdd.index].vf.datasource)
  {
    ogg_free(cdd.index);
  }
#endif
#endif

  load_param(&cdd.cycles, sizeof(cdd.cycles));
  load_param(&cdd.latency, sizeof(cdd.latency));
  load_param(&cdd.index, sizeof(cdd.index));
  load_param(&cdd.lba, sizeof(cdd.lba));
  load_param(&cdd.scanOffset, sizeof(cdd.scanOffset));
  load_param(&cdd.volume, sizeof(cdd.volume));
  load_param(&cdd.status, sizeof(cdd.status));

  /* adjust current LBA within track limit */
  lba = cdd.lba;
  if (lba < cdd.toc.tracks[cdd.index].start)
  {
    lba = cdd.toc.tracks[cdd.index].start;
  }

  /* seek to current track position */
  if (!cdd.index)
  {
    /* DATA track */
    if (cdd.toc.tracks[0].fd)
    {
      pm_seek(cdd.toc.tracks[0].fd, lba * cdd.sectorSize, SEEK_SET);
    }
  }
#ifdef USE_LIBTREMOR
  else if (cdd.toc.tracks[cdd.index].vf.seekable)
  {
#ifdef DISABLE_MANY_OGG_OPEN_FILES
    /* VORBIS file need to be opened first */
    ov_open(cdd.toc.tracks[cdd.index].fd,&cdd.toc.tracks[cdd.index].vf,0,0);
#endif
    /* VORBIS AUDIO track */
    ov_pcm_seek(&cdd.toc.tracks[cdd.index].vf, (lba - cdd.toc.tracks[cdd.index].start) * 588 - cdd.toc.tracks[cdd.index].offset);
  }
#endif
#if 0
  else if (cdd.toc.tracks[cdd.index].fd)
  {
    /* PCM AUDIO track */
    fseek(cdd.toc.tracks[cdd.index].fd, (lba * 2352) - cdd.toc.tracks[cdd.index].offset, SEEK_SET);
  }
#else
  else
  {
    cdd_change_track(cdd.index, lba);
  }
#endif

  return bufferptr;
}