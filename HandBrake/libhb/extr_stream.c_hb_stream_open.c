#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int flags; } ;
typedef  TYPE_1__ hb_title_t ;
struct TYPE_14__ {int has_IDRs; int scan; struct TYPE_14__* path; int /*<<< orphan*/ * file_handle; TYPE_1__* title; int /*<<< orphan*/ * h; } ;
typedef  TYPE_2__ hb_stream_t ;
typedef  int /*<<< orphan*/  hb_handle_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int HBTF_NO_IDR ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ffmpeg_open (TYPE_2__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/ * hb_fopen (char const*,char*) ; 
 int /*<<< orphan*/  hb_log (char*,...) ; 
 scalar_t__ hb_stream_get_type (TYPE_2__*) ; 
 int /*<<< orphan*/  hb_stream_seek (TYPE_2__*,int) ; 
 int /*<<< orphan*/  prune_streams (TYPE_2__*) ; 
 TYPE_2__* strdup (char const*) ; 

hb_stream_t *
hb_stream_open(hb_handle_t *h, const char *path, hb_title_t *title, int scan)
{
    if (title == NULL)
    {
        hb_log("hb_stream_open: title is null");
        return NULL;
    }

    FILE *f = hb_fopen(path, "rb");
    if ( f == NULL )
    {
        hb_log( "hb_stream_open: open %s failed", path );
        return NULL;
    }

    hb_stream_t *d = calloc( sizeof( hb_stream_t ), 1 );
    if ( d == NULL )
    {
        fclose( f );
        hb_log( "hb_stream_open: can't allocate space for %s stream state", path );
        return NULL;
    }

    if (!(title->flags & HBTF_NO_IDR))
    {
        d->has_IDRs = 1;
    }

    /*
     * If it's something we can deal with (MPEG2 PS or TS) return a stream
     * reference structure & null otherwise.
     */
    d->h = h;
    d->file_handle = f;
    d->title = title;
    d->scan = scan;
    d->path = strdup( path );
    if (d->path != NULL )
    {
        if (hb_stream_get_type( d ) != 0)
        {
            if( !scan )
            {
                prune_streams( d );
            }
            // reset to beginning of file and reset some stream
            // state information
            hb_stream_seek( d, 0. );
            return d;
        }
        fclose( d->file_handle );
        d->file_handle = NULL;
        if ( ffmpeg_open( d, title, scan ) )
        {
            return d;
        }
    }
    if ( d->file_handle )
    {
        fclose( d->file_handle );
    }
    if (d->path)
    {
        free( d->path );
    }
    hb_log( "hb_stream_open: open %s failed", path );
    free( d );
    return NULL;
}