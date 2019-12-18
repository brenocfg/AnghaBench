#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {int start; int end; int offset; TYPE_4__* fd; } ;
typedef  TYPE_3__ track_t ;
typedef  int /*<<< orphan*/  tmp_name ;
typedef  int /*<<< orphan*/  tmp_ext ;
struct TYPE_15__ {int size; } ;
typedef  TYPE_4__ pm_file ;
typedef  int /*<<< orphan*/  exts ;
struct TYPE_16__ {int track_count; TYPE_2__* tracks; } ;
typedef  TYPE_5__ cue_data_t ;
struct TYPE_12__ {int last; int end; TYPE_3__* tracks; } ;
struct TYPE_17__ {TYPE_1__ toc; } ;
struct TYPE_13__ {char* fname; int type; int sector_offset; int sector_xlength; scalar_t__ pregap; } ;
struct TYPE_11__ {int cdda_type; } ;

/* Variables and functions */
 int CT_ISO ; 
 int CT_MP3 ; 
 int CT_UNKNOWN ; 
 int /*<<< orphan*/  EL_STATUS ; 
 int /*<<< orphan*/  PicoCDLoadProgressCB (char const*,int) ; 
 TYPE_10__* Pico_mcd ; 
 TYPE_9__ cdd ; 
 int /*<<< orphan*/  cue_destroy (TYPE_5__*) ; 
 TYPE_5__* cue_parse (char const*) ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,...) ; 
 int handle_mp3 (char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 TYPE_4__* pm_open (char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char const*,int) ; 
 int /*<<< orphan*/  sprintf_lba (char*,int,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  to_upper (char*,char*) ; 

int load_cd_image(const char *cd_img_name, int *type)
{
  static const char *exts[] = {
    "%02d.mp3", " %02d.mp3", "-%02d.mp3", "_%02d.mp3", " - %02d.mp3",
    "%d.mp3", " %d.mp3", "-%d.mp3", "_%d.mp3", " - %d.mp3",
  };
  int i, j, n, lba, index, length, ret;
  int iso_name_len, missed, cd_img_sectors;
  char tmp_name[256], tmp_ext[10], tmp_ext_u[10];
  track_t *tracks = cdd.toc.tracks;
  cue_data_t *cue_data = NULL;
  pm_file *pmf;

  if (PicoCDLoadProgressCB != NULL)
    PicoCDLoadProgressCB(cd_img_name, 1);

  Pico_mcd->cdda_type = CT_UNKNOWN;

  /* is this a .cue? */
  cue_data = cue_parse(cd_img_name);
  if (cue_data != NULL) {
    cd_img_name = cue_data->tracks[1].fname;
    *type = cue_data->tracks[1].type;
  }

  pmf = pm_open(cd_img_name);
  if (pmf == NULL)
  {
    if (cue_data != NULL)
      cue_destroy(cue_data);
    return -1;
  }
  tracks[0].fd = pmf;

  if (*type == CT_ISO)
       cd_img_sectors = pmf->size >>= 11;  // size in sectors
  else cd_img_sectors = pmf->size /= 2352;

  // cdd.c operates with lba - 150
  tracks[0].start = 0;
  tracks[0].end = cd_img_sectors;
  tracks[0].offset = 0;

  sprintf_lba(tmp_ext, sizeof(tmp_ext), 0);
  elprintf(EL_STATUS, "Track  1: %s %9i DATA  %s",
    tmp_ext, tracks[0].end, cd_img_name);

  lba = cd_img_sectors;

  if (cue_data != NULL)
  {
    if (cue_data->tracks[2].fname == NULL) {
      // NULL fname means track2 is in same file as track1
      lba = tracks[0].end = cue_data->tracks[2].sector_offset;
    }
    i = 100 / cue_data->track_count + 1; // progress display

    for (n = 2; n <= cue_data->track_count; n++)
    {
      if (PicoCDLoadProgressCB != NULL)
        PicoCDLoadProgressCB(cd_img_name, i * n);

      index = n - 1;
      lba += cue_data->tracks[n].pregap;
      if (cue_data->tracks[n].type == CT_MP3) {
        ret = handle_mp3(cue_data->tracks[n].fname, index);
        if (ret < 0)
          break;
        length = ret;
      }
      else if (cue_data->tracks[n].fname != NULL)
      {
        pm_file *f = pm_open(cue_data->tracks[n].fname);
        if (f != NULL)
        {
          // assume raw, ignore header for wav..
          tracks[index].fd = f;
          tracks[index].offset = cue_data->tracks[n].sector_offset;
          length = f->size / 2352;
        }
        else
        {
          elprintf(EL_STATUS, "track %2i (%s): can't determine length",
            n, cue_data->tracks[n].fname);
          tracks[index].offset = 0;
          length = 2*75;
        }
      }
      else
      {
        if (n < cue_data->track_count)
          length = cue_data->tracks[n+1].sector_offset -
            cue_data->tracks[n].sector_offset;
        else
          length = cd_img_sectors - cue_data->tracks[n].sector_offset;
        tracks[index].offset = cue_data->tracks[n].sector_offset;
      }

      if (cue_data->tracks[n].sector_xlength != 0)
        // overriden by custom cue command
        length = cue_data->tracks[n].sector_xlength;

      Pico_mcd->cdda_type = cue_data->tracks[n].type;

      tracks[index].start = lba;
      lba += length;
      tracks[index].end = lba;

      sprintf_lba(tmp_ext, sizeof(tmp_ext), tracks[index].start);
      elprintf(EL_STATUS, "Track %2i: %s %9i AUDIO %s",
        n, tmp_ext, length, cue_data->tracks[n].fname);
    }
    goto finish;
  }

  /* mp3 track autosearch, Gens-like */
  iso_name_len = strlen(cd_img_name);
  if (iso_name_len >= sizeof(tmp_name))
    iso_name_len = sizeof(tmp_name) - 1;

  for (n = 2, i = 0, missed = 0; i < 100 && missed < 4; i++)
  {
    if (PicoCDLoadProgressCB != NULL && i > 1)
      PicoCDLoadProgressCB(cd_img_name, i + (100-i)*missed/4);

    for (j = 0; j < sizeof(exts)/sizeof(char *); j++)
    {
      int ext_len;
      char *p;

      index = n - 1;

      snprintf(tmp_ext, sizeof(tmp_ext), exts[j], i);
      ext_len = strlen(tmp_ext);
      to_upper(tmp_ext_u, tmp_ext);

      memcpy(tmp_name, cd_img_name, iso_name_len + 1);
      p = tmp_name + iso_name_len - 4;

      strcpy(p, tmp_ext);
      ret = handle_mp3(tmp_name, index);
      if (ret <= 0) {
        strcpy(p, tmp_ext_u);
        ret = handle_mp3(tmp_name, index);
      }

      if (ret <= 0 && i > 1 && iso_name_len > ext_len) {
        p = tmp_name + iso_name_len - ext_len;
        strcpy(p, tmp_ext);
        ret = handle_mp3(tmp_name, index);
        if (ret <= 0) {
          strcpy(p, tmp_ext_u);
          ret = handle_mp3(tmp_name, index);
        }
      }

      if (ret > 0)
      {
        length = ret;
        tracks[index].start = lba;
        lba += length;
        tracks[index].end = lba;

        Pico_mcd->cdda_type = CT_MP3;

        sprintf_lba(tmp_ext, sizeof(tmp_ext), tracks[index].start);
        elprintf(EL_STATUS, "Track %2i: %s %9i AUDIO - %s",
          n, tmp_ext, length, tmp_name);

        n++;
        missed = 0;
        break;
      }
    }
    if (ret <= 0 && i > 1)
      missed++;
  }

finish:
  cdd.toc.last = n - 1;
  cdd.toc.end = lba;

  sprintf_lba(tmp_ext, sizeof(tmp_ext), cdd.toc.end);
  elprintf(EL_STATUS, "End CD -  %s\n", tmp_ext);

  if (PicoCDLoadProgressCB != NULL)
    PicoCDLoadProgressCB(cd_img_name, 100);

  if (cue_data != NULL)
    cue_destroy(cue_data);

  return 0;
}