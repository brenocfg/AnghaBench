#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  list_filter; int /*<<< orphan*/ * file; int /*<<< orphan*/ * encoder_level; int /*<<< orphan*/ * encoder_profile; int /*<<< orphan*/ * encoder_options; int /*<<< orphan*/ * encoder_tune; int /*<<< orphan*/ * encoder_preset; int /*<<< orphan*/  metadata; int /*<<< orphan*/  list_attachment; int /*<<< orphan*/  list_audio; int /*<<< orphan*/  list_chapter; int /*<<< orphan*/  list_subtitle; int /*<<< orphan*/ * json; } ;
typedef  TYPE_1__ hb_job_t ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  hb_attachment_list_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_audio_list_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_chapter_list_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_filter_list_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_metadata_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_subtitle_list_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 void* strdup (int /*<<< orphan*/ *) ; 

hb_job_t* hb_job_copy(hb_job_t * job)
{
    hb_job_t      * job_copy;

    /* Copy the job */
    job_copy        = calloc( sizeof( hb_job_t ), 1 );
    if (job_copy == NULL)
        return NULL;

    if (job->json != NULL)
    {
        // JSON jobs should only have the json string set.
        job_copy->json = strdup(job->json);
        return job_copy;
    }
    memcpy( job_copy, job, sizeof( hb_job_t ) );

    job_copy->list_subtitle = hb_subtitle_list_copy( job->list_subtitle );
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

    job_copy->list_filter = hb_filter_list_copy( job->list_filter );

    return job_copy;
}