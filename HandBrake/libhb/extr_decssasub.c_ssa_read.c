#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_6__ {scalar_t__ start_time; scalar_t__ stop_time; int /*<<< orphan*/  file; TYPE_1__* job; } ;
typedef  TYPE_2__ hb_work_private_t ;
typedef  int /*<<< orphan*/  hb_buffer_t ;
struct TYPE_5__ {scalar_t__ reader_pts_offset; scalar_t__ pts_to_stop; scalar_t__ pts_to_start; } ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/ * decode_line_to_mkv_ssa (TYPE_2__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * hb_buffer_eof_init () ; 
 scalar_t__ hb_getline (char**,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static hb_buffer_t * ssa_read( hb_work_private_t * pv )
{
    hb_buffer_t * out;

    if (pv->job->reader_pts_offset == AV_NOPTS_VALUE)
    {
        // We need to wait for reader to initialize it's pts offset so that
        // we know where to start reading SSA.
        return NULL;
    }
    if (pv->start_time == AV_NOPTS_VALUE)
    {
        pv->start_time = pv->job->reader_pts_offset;
        if (pv->job->pts_to_stop > 0)
        {
            pv->stop_time = pv->job->pts_to_start + pv->job->pts_to_stop;
        }
    }
    while (!feof(pv->file))
    {
        char    * line = NULL;
        ssize_t   len;
        size_t    size = 0;

        len = hb_getline(&line, &size, pv->file);
        if (len > 0 && line != NULL)
        {
            out = decode_line_to_mkv_ssa(pv, line, len);
            if (out != NULL)
            {
                free(line);
                return out;
            }
        }
        free(line);
        if (len < 0)
        {
            // Error or EOF
            out = hb_buffer_eof_init();
            return out;
        }
    }
    out = hb_buffer_eof_init();

    return out;
}