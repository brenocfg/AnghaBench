#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hb_subtitle_t ;
struct TYPE_3__ {void* encoder_preset; void* encoder_tune; void* encoder_options; void* encoder_profile; void* encoder_level; void* file; int /*<<< orphan*/  metadata; int /*<<< orphan*/  list_attachment; int /*<<< orphan*/  list_filter; int /*<<< orphan*/  list_subtitle; int /*<<< orphan*/  list_audio; int /*<<< orphan*/  list_chapter; int /*<<< orphan*/ * json; } ;
typedef  TYPE_1__ hb_job_t ;
typedef  int /*<<< orphan*/  hb_filter_object_t ;
typedef  int /*<<< orphan*/  hb_chapter_t ;
typedef  int /*<<< orphan*/  hb_audio_t ;
typedef  int /*<<< orphan*/  hb_attachment_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  hb_attachment_close (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hb_audio_close (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hb_chapter_close (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hb_filter_close (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hb_list_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_list_item (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_list_rem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_metadata_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_subtitle_close (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void job_clean( hb_job_t * job )
{
    if (job)
    {
        hb_chapter_t *chapter;
        hb_audio_t *audio;
        hb_subtitle_t *subtitle;
        hb_filter_object_t *filter;
        hb_attachment_t *attachment;

        free((void*)job->json);
        job->json = NULL;
        free(job->encoder_preset);
        job->encoder_preset = NULL;
        free(job->encoder_tune);
        job->encoder_tune = NULL;
        free(job->encoder_options);
        job->encoder_options = NULL;
        free(job->encoder_profile);
        job->encoder_profile = NULL;
        free(job->encoder_level);
        job->encoder_level = NULL;
        free(job->file);
        job->file = NULL;

        // clean up chapter list
        while( ( chapter = hb_list_item( job->list_chapter, 0 ) ) )
        {
            hb_list_rem( job->list_chapter, chapter );
            hb_chapter_close( &chapter );
        }
        hb_list_close( &job->list_chapter );

        // clean up audio list
        while( ( audio = hb_list_item( job->list_audio, 0 ) ) )
        {
            hb_list_rem( job->list_audio, audio );
            hb_audio_close( &audio );
        }
        hb_list_close( &job->list_audio );

        // clean up subtitle list
        while( ( subtitle = hb_list_item( job->list_subtitle, 0 ) ) )
        {
            hb_list_rem( job->list_subtitle, subtitle );
            hb_subtitle_close( &subtitle );
        }
        hb_list_close( &job->list_subtitle );

        // clean up filter list
        while( ( filter = hb_list_item( job->list_filter, 0 ) ) )
        {
            hb_list_rem( job->list_filter, filter );
            hb_filter_close( &filter );
        }
        hb_list_close( &job->list_filter );

        // clean up attachment list
        while( ( attachment = hb_list_item( job->list_attachment, 0 ) ) )
        {
            hb_list_rem( job->list_attachment, attachment );
            hb_attachment_close( &attachment );
        }
        hb_list_close( &job->list_attachment );

        // clean up metadata
        hb_metadata_close( &job->metadata );
    }
}