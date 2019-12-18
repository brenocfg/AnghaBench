#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  source; int /*<<< orphan*/  iso639_2; } ;
typedef  TYPE_5__ hb_subtitle_t ;
typedef  int /*<<< orphan*/  hb_list_t ;
struct TYPE_19__ {int /*<<< orphan*/  force; } ;
struct TYPE_21__ {int /*<<< orphan*/ * list_filter; int /*<<< orphan*/ * h; int /*<<< orphan*/ * file; int /*<<< orphan*/ * encoder_level; int /*<<< orphan*/ * encoder_profile; int /*<<< orphan*/ * encoder_options; int /*<<< orphan*/ * encoder_tune; int /*<<< orphan*/ * encoder_preset; int /*<<< orphan*/ * metadata; int /*<<< orphan*/ * list_attachment; int /*<<< orphan*/ * list_audio; int /*<<< orphan*/ * list_chapter; int /*<<< orphan*/ * list_subtitle; TYPE_4__ select_subtitle_config; TYPE_3__* title; scalar_t__ indepth_scan; int /*<<< orphan*/ * json; } ;
typedef  TYPE_6__ hb_job_t ;
typedef  int /*<<< orphan*/  hb_handle_t ;
struct TYPE_16__ {int /*<<< orphan*/  iso639_2; } ;
struct TYPE_17__ {TYPE_1__ lang; } ;
struct TYPE_22__ {TYPE_2__ config; } ;
typedef  TYPE_7__ hb_audio_t ;
typedef  int /*<<< orphan*/  audio_lang ;
struct TYPE_18__ {int /*<<< orphan*/ * list_subtitle; } ;

/* Variables and functions */
 TYPE_6__* calloc (int,int) ; 
 int /*<<< orphan*/ * hb_attachment_list_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_audio_list_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_chapter_list_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_filter_list_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_job_close (TYPE_6__**) ; 
 int /*<<< orphan*/  hb_list_add (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int hb_list_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_list_init () ; 
 void* hb_list_item (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hb_log (char*) ; 
 int /*<<< orphan*/ * hb_metadata_copy (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_subtitle_can_force (int /*<<< orphan*/ ) ; 
 TYPE_6__* hb_subtitle_copy (TYPE_5__*) ; 
 int /*<<< orphan*/ * hb_subtitle_list_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_6__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 void* strdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hb_add_internal( hb_handle_t * h, hb_job_t * job, hb_list_t *list_pass )
{
    hb_job_t      * job_copy;
    hb_audio_t    * audio;
    hb_subtitle_t * subtitle;
    int             i;
    char            audio_lang[4];

    /* Copy the job */
    job_copy                  = calloc( sizeof( hb_job_t ), 1 );
    memcpy(job_copy, job, sizeof(hb_job_t));
    job_copy->json            = NULL;
    job_copy->encoder_preset  = NULL;
    job_copy->encoder_tune    = NULL;
    job_copy->encoder_profile = NULL;
    job_copy->encoder_level   = NULL;
    job_copy->encoder_options = NULL;
    job_copy->file            = NULL;
    job_copy->list_chapter    = NULL;
    job_copy->list_audio      = NULL;
    job_copy->list_subtitle   = NULL;
    job_copy->list_filter     = NULL;
    job_copy->list_attachment = NULL;
    job_copy->metadata        = NULL;

    /* If we're doing Foreign Audio Search, copy all subtitles matching the
     * first audio track language we find in the audio list.
     *
     * Otherwise, copy all subtitles found in the input job (which can be
     * manually selected by the user, or added after the Foreign Audio
     * Search pass). */
    memset( audio_lang, 0, sizeof( audio_lang ) );

    if( job->indepth_scan )
    {

        /* Find the first audio language that is being encoded, then add all the
         * matching subtitles for that language. */
        for( i = 0; i < hb_list_count( job->list_audio ); i++ )
        {
            if( ( audio = hb_list_item( job->list_audio, i ) ) )
            {
                strncpy( audio_lang, audio->config.lang.iso639_2, sizeof( audio_lang ) );
                break;
            }
        }

        /*
         * If doing a subtitle scan then add all the matching subtitles for this
         * language.
         */
        job_copy->list_subtitle = hb_list_init();

        for( i = 0; i < hb_list_count( job->title->list_subtitle ); i++ )
        {
            subtitle = hb_list_item( job->title->list_subtitle, i );
            if( strcmp( subtitle->iso639_2, audio_lang ) == 0 &&
                hb_subtitle_can_force( subtitle->source ) )
            {
                /* Matched subtitle language with audio language, so add this to
                 * our list to scan.
                 *
                 * We will update the subtitle list on the next pass later, after
                 * the subtitle scan pass has completed. */
                hb_list_add( job_copy->list_subtitle,
                             hb_subtitle_copy( subtitle ) );
            }
        }
        int count = hb_list_count(job_copy->list_subtitle);
        if (count == 0 ||
            (count == 1 && !job_copy->select_subtitle_config.force))
        {
            hb_log("Skipping subtitle scan.  No suitable subtitle tracks.");
            hb_job_close(&job_copy);
            return;
        }
    }
    else
    {
        /* Copy all subtitles from the input job to title_copy/job_copy. */
        job_copy->list_subtitle = hb_subtitle_list_copy( job->list_subtitle );
    }

    job_copy->list_chapter = hb_chapter_list_copy( job->list_chapter );
    job_copy->list_audio = hb_audio_list_copy( job->list_audio );
    job_copy->list_attachment = hb_attachment_list_copy( job->list_attachment );
    job_copy->metadata = hb_metadata_copy( job->metadata );

    if (job->encoder_preset != NULL)
        job_copy->encoder_preset = strdup(job->encoder_preset);
    if (job->encoder_tune != NULL)
        job_copy->encoder_tune = strdup(job->encoder_tune);
    if (job->encoder_options != NULL)
        job_copy->encoder_options = strdup(job->encoder_options);
    if (job->encoder_profile != NULL)
        job_copy->encoder_profile = strdup(job->encoder_profile);
    if (job->encoder_level != NULL)
        job_copy->encoder_level = strdup(job->encoder_level);
    if (job->file != NULL)
        job_copy->file = strdup(job->file);

    job_copy->h     = h;

    /* Copy the job filter list */
    job_copy->list_filter = hb_filter_list_copy( job->list_filter );

    /* Add the job to the list */
    hb_list_add( list_pass, job_copy );
}