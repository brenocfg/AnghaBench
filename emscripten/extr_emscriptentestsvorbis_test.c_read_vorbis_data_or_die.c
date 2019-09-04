#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int rate; } ;
typedef  TYPE_1__ vorbis_info ;
typedef  int /*<<< orphan*/  vorbis_dsp_state ;
typedef  int /*<<< orphan*/  vorbis_comment ;
typedef  int /*<<< orphan*/  vorbis_block ;
typedef  int /*<<< orphan*/  ogg_sync_state ;
typedef  int /*<<< orphan*/  ogg_stream_state ;
typedef  int /*<<< orphan*/  ogg_page ;
typedef  int /*<<< orphan*/  ogg_packet ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 
 scalar_t__ ogg_page_eos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ogg_page_serialno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ogg_stream_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ogg_stream_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ogg_stream_packetout (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ogg_stream_pagein (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* ogg_sync_buffer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ogg_sync_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ogg_sync_init (int /*<<< orphan*/ *) ; 
 int ogg_sync_pageout (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ogg_sync_wrote (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vorbis_block_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vorbis_block_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vorbis_comment_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vorbis_comment_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vorbis_dsp_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vorbis_info_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  vorbis_info_init (TYPE_1__*) ; 
 scalar_t__ vorbis_synthesis (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vorbis_synthesis_blockin (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vorbis_synthesis_headerin (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vorbis_synthesis_init (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int vorbis_synthesis_pcmout (int /*<<< orphan*/ *,float***) ; 
 int /*<<< orphan*/  vorbis_synthesis_read (int /*<<< orphan*/ *,int) ; 

void
read_vorbis_data_or_die (const char *filename, int srate, float * data, int count)
{
  ogg_sync_state   oy;
  ogg_stream_state os;
  ogg_page         og;
  ogg_packet       op;

  vorbis_info      vi;
  vorbis_comment   vc;
  vorbis_dsp_state vd;
  vorbis_block     vb;

  FILE *file;
  char *buffer;
  int  bytes;
  int eos = 0;
  int i;
  int read_total = 0 ;

  if ((file = fopen (filename, "rb")) == NULL) {
    printf("\n\nError : fopen failed : %s\n", strerror (errno)) ;
    exit (1) ;
  }

  ogg_sync_init (&oy);

  {
    /* fragile!  Assumes all of our headers will fit in the first 8kB,
       which currently they will */
    buffer = ogg_sync_buffer (&oy,8192);
    bytes = fread (buffer,1,8192,file);
    ogg_sync_wrote (&oy,bytes);

    if(ogg_sync_pageout (&oy,&og) != 1) {
      if(bytes < 8192) {
        printf ("Out of data.\n") ;
          goto done_decode ;
      }

      fprintf (stderr,"Input does not appear to be an Ogg bitstream.\n");
      exit (1);
    }

    ogg_stream_init (&os,ogg_page_serialno(&og));

    vorbis_info_init (&vi);
    vorbis_comment_init (&vc);
    if (ogg_stream_pagein (&os,&og) < 0) {
      fprintf (stderr,"Error reading first page of Ogg bitstream data.\n");
      exit (1);
    }

    if (ogg_stream_packetout(&os,&op) != 1) {
      fprintf (stderr,"Error reading initial header packet.\n");
      exit (1);
    }

    if (vorbis_synthesis_headerin (&vi,&vc,&op) < 0) {
      fprintf (stderr,"This Ogg bitstream does not contain Vorbis "
          "audio data.\n");
      exit (1);
    }

    i = 0;
    while ( i < 2) {
      while (i < 2) {

        int result = ogg_sync_pageout (&oy,&og);
        if(result == 0)
          break;
        if(result==1) {
          ogg_stream_pagein(&os,&og);

          while (i < 2) {
            result = ogg_stream_packetout (&os,&op);
            if (result == 0) break;
            if (result < 0) {
              fprintf (stderr,"Corrupt secondary header.  Exiting.\n");
              exit(1);
            }
            vorbis_synthesis_headerin (&vi,&vc,&op);
            i++;
          }
        }
      }

      buffer = ogg_sync_buffer (&oy,4096);
      bytes = fread (buffer,1,4096,file);
      if (bytes == 0 && i < 2) {
        fprintf (stderr,"End of file before finding all Vorbis headers!\n");
        exit (1);
      }

      ogg_sync_wrote (&oy,bytes);
    }

    if (vi.rate != srate) {
      printf ("\n\nError : File '%s' has sample rate of %ld when it should be %d.\n\n", filename, vi.rate, srate);
      exit (1) ;
    }

    vorbis_synthesis_init (&vd,&vi);
    vorbis_block_init (&vd,&vb);

    while(!eos) {
      while (!eos) {
        int result = ogg_sync_pageout (&oy,&og);
        if (result == 0)
          break;
        if (result < 0) {
          fprintf (stderr,"Corrupt or missing data in bitstream; "
                   "continuing...\n");
        } else {
          ogg_stream_pagein (&os,&og);
          while (1) {
            result = ogg_stream_packetout (&os,&op);

            if (result == 0)
              break;
            if (result < 0) {
              /* no reason to complain; already complained above */
            } else {
              float **pcm;
              int samples;

              if (vorbis_synthesis (&vb,&op) == 0)
                vorbis_synthesis_blockin(&vd,&vb);
              while ((samples = vorbis_synthesis_pcmout (&vd,&pcm)) > 0 && read_total < count) {
                int bout = samples < count ? samples : count;
                bout = read_total + bout > count ? count - read_total : bout;

                memcpy (data + read_total, pcm[0], bout * sizeof (float)) ;

                vorbis_synthesis_read (&vd,bout);
                read_total += bout ;
              }
            }
          }

          if (ogg_page_eos (&og)) eos = 1;
        }
      }

      if (!eos) {
        buffer = ogg_sync_buffer (&oy,4096);
        bytes = fread (buffer,1,4096,file);
        ogg_sync_wrote (&oy,bytes);
        if (bytes == 0) eos = 1;
      }
    }

    ogg_stream_clear (&os);

    vorbis_block_clear (&vb);
    vorbis_dsp_clear (&vd);
    vorbis_comment_clear (&vc);
    vorbis_info_clear (&vi);
  }
done_decode:

  /* OK, clean up the framer */
  ogg_sync_clear (&oy);

  fclose (file) ;
}