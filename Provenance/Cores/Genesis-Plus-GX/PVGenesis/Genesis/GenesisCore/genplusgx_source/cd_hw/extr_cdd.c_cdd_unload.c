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
struct TYPE_7__ {int last; TYPE_1__* tracks; } ;
struct TYPE_8__ {scalar_t__ sectorSize; TYPE_3__ toc; scalar_t__ loaded; } ;
struct TYPE_6__ {scalar_t__ datasource; } ;
struct TYPE_5__ {scalar_t__ fd; TYPE_2__ vf; } ;

/* Variables and functions */
 TYPE_4__ cdd ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  ov_clear (TYPE_2__*) ; 

void cdd_unload(void)
{
  if (cdd.loaded)
  {
    int i;

    /* close CD tracks */
    for (i=0; i<cdd.toc.last; i++)
    {
#ifdef USE_LIBTREMOR
      if (cdd.toc.tracks[i].vf.datasource)
      {
        /* close VORBIS file */
        ov_clear(&cdd.toc.tracks[i].vf);
      }
      else
#endif
      {
        if (cdd.toc.tracks[i].fd)
        {
          /* close file */
          fclose(cdd.toc.tracks[i].fd);

          /* detect single file images */
          if (cdd.toc.tracks[i+1].fd == cdd.toc.tracks[i].fd)
          {
            /* exit loop */
            i = cdd.toc.last;
          }
        }
      }
    }

    /* CD unloaded */
    cdd.loaded = 0;
  }

  /* reset TOC */
  memset(&cdd.toc, 0x00, sizeof(cdd.toc));
    
  /* unknown CD image file format */
  cdd.sectorSize = 0;
}