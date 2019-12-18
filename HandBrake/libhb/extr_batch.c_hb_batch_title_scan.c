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
typedef  int /*<<< orphan*/  hb_title_t ;
typedef  int /*<<< orphan*/  hb_stream_t ;
struct TYPE_3__ {int /*<<< orphan*/  h; int /*<<< orphan*/  list_file; } ;
typedef  TYPE_1__ hb_batch_t ;

/* Variables and functions */
 char* hb_list_item (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hb_log (char*,char*) ; 
 int /*<<< orphan*/  hb_stream_close (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * hb_stream_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * hb_stream_title_scan (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_title_close (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * hb_title_init (char*,int) ; 

hb_title_t * hb_batch_title_scan( hb_batch_t * d, int t )
{

    hb_title_t   * title;
    char         * filename;
    hb_stream_t  * stream;

    if ( t < 0 )
        return NULL;

    filename = hb_list_item( d->list_file, t - 1 );
    if ( filename == NULL )
        return NULL;

    hb_log( "batch: scanning %s", filename );
    title = hb_title_init( filename, t );
    stream = hb_stream_open(d->h, filename, title, 1);
    if ( stream == NULL )
    {
        hb_title_close( &title );
        return NULL;
    }

    title = hb_stream_title_scan( stream, title );
    hb_stream_close( &stream );

    return title;
}