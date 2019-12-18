#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ cdda_type; } ;
struct TYPE_8__ {int last; TYPE_1__* tracks; } ;
struct TYPE_9__ {int loaded; scalar_t__ status; scalar_t__ sectorSize; TYPE_3__ toc; } ;
struct TYPE_7__ {scalar_t__ datasource; } ;
struct TYPE_6__ {scalar_t__ fd; TYPE_2__ vf; } ;

/* Variables and functions */
 scalar_t__ CD_OPEN ; 
 scalar_t__ CT_MP3 ; 
 scalar_t__ NO_DISC ; 
 TYPE_5__* Pico_mcd ; 
 TYPE_4__ cdd ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  ov_clear (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_close (int /*<<< orphan*/ *) ; 

int cdd_unload(void)
{
  int was_loaded = cdd.loaded;

  if (cdd.loaded)
  {
    int i;

    /* close CD tracks */
    if (cdd.toc.tracks[0].fd)
    {
      pm_close(cdd.toc.tracks[0].fd);
      cdd.toc.tracks[0].fd = NULL;
    }

    for (i = 1; i < cdd.toc.last; i++)
    {
#ifdef USE_LIBTREMOR
      if (cdd.toc.tracks[i].vf.datasource)
      {
        /* close VORBIS file (if still opened) */
        ov_clear(&cdd.toc.tracks[i].vf);
      }
      else
#endif
      if (cdd.toc.tracks[i].fd)
      {
        /* close file */
        if (Pico_mcd->cdda_type == CT_MP3)
          fclose(cdd.toc.tracks[i].fd);
        else
          pm_close(cdd.toc.tracks[0].fd);

        /* detect single file images */
        if (cdd.toc.tracks[i+1].fd == cdd.toc.tracks[i].fd)
        {
          /* exit loop */
          i = cdd.toc.last;
        }
      }
    }

    /* CD unloaded */
    cdd.loaded = 0;

    if (cdd.status != CD_OPEN)
      cdd.status = NO_DISC;
  }

  /* reset TOC */
  memset(&cdd.toc, 0x00, sizeof(cdd.toc));
    
  /* unknown CD image file format */
  cdd.sectorSize = 0;

  return was_loaded;
}