#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_12__ {int index; int preview_count; } ;
typedef  TYPE_2__ hb_title_t ;
struct TYPE_14__ {int /*<<< orphan*/ * path; int /*<<< orphan*/  list_title; } ;
struct TYPE_11__ {int /*<<< orphan*/  state; } ;
struct TYPE_13__ {TYPE_6__ title_set; scalar_t__ scan_die; int /*<<< orphan*/  scan_thread; int /*<<< orphan*/  state_lock; TYPE_1__ state; } ;
typedef  TYPE_3__ hb_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  HB_STATE_SCANDONE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hb_get_cpu_count () ; 
 char* hb_get_cpu_name () ; 
 char* hb_get_cpu_platform_name () ; 
 int hb_list_count (int /*<<< orphan*/ ) ; 
 TYPE_2__* hb_list_item (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hb_list_rem (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  hb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_log (char*,char const*,...) ; 
 int /*<<< orphan*/  hb_qsv_info_print () ; 
 int /*<<< orphan*/  hb_remove_previews (TYPE_3__*) ; 
 int /*<<< orphan*/  hb_scan_init (TYPE_3__*,scalar_t__*,char const*,int,TYPE_6__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_title_close (TYPE_2__**) ; 
 int /*<<< orphan*/  hb_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_hardware_disabled () ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,char const*) ; 

void hb_scan( hb_handle_t * h, const char * path, int title_index,
              int preview_count, int store_previews, uint64_t min_duration )
{
    hb_title_t * title;

    // Check if scanning is necessary.
    if (h->title_set.path != NULL && !strcmp(h->title_set.path, path))
    {
        // Current title_set path matches requested path.
        // Check if the requested title has already been scanned.
        int ii;
        for (ii = 0; ii < hb_list_count(h->title_set.list_title); ii++)
        {
            title = hb_list_item(h->title_set.list_title, ii);
            if (title->index == title_index)
            {
                // In some cases, we don't care what the preview count is.
                // E.g. when rescanning at the start of a job. In these
                // cases, the caller can set preview_count to -1 to tell
                // us to use the same count as the previous scan, if known.
                if (preview_count < 0)
                {
                    preview_count = title->preview_count;
                }
                if (preview_count == title->preview_count)
                {
                    // Title has already been scanned.
                    hb_lock( h->state_lock );
                    h->state.state = HB_STATE_SCANDONE;
                    hb_unlock( h->state_lock );
                    return;
                }
            }
        }
    }
    if (preview_count < 0)
    {
        preview_count = 10;
    }

    h->scan_die = 0;

    /* Clean up from previous scan */
    hb_remove_previews( h );
    while( ( title = hb_list_item( h->title_set.list_title, 0 ) ) )
    {
        hb_list_rem( h->title_set.list_title, title );
        hb_title_close( &title );
    }
    free((char*)h->title_set.path);
    h->title_set.path = NULL;

    /* Print CPU info here so that it's in all scan and encode logs */
    const char *cpu_name = hb_get_cpu_name();
    const char *cpu_type = hb_get_cpu_platform_name();
    hb_log("CPU: %s", cpu_name != NULL ? cpu_name : "");
    if (cpu_type != NULL)
    {
        hb_log(" - %s", cpu_type);
    }
    hb_log(" - logical processor count: %d", hb_get_cpu_count());

#if HB_PROJECT_FEATURE_QSV
    if (!is_hardware_disabled())
    {
        /* Print QSV info here so that it's in all scan and encode logs */
        hb_qsv_info_print();
    }
#endif

    hb_log( "hb_scan: path=%s, title_index=%d", path, title_index );
    h->scan_thread = hb_scan_init( h, &h->scan_die, path, title_index,
                                   &h->title_set, preview_count,
                                   store_previews, min_duration );
}