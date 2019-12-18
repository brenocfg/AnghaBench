#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hb_handle_t ;
struct TYPE_4__ {int title_count; int /*<<< orphan*/ * bd; int /*<<< orphan*/  path; int /*<<< orphan*/  disc_info; int /*<<< orphan*/ * title_info; int /*<<< orphan*/ * h; } ;
typedef  TYPE_1__ hb_bd_t ;
typedef  int /*<<< orphan*/  BLURAY_TITLE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  TITLES_RELEVANT ; 
 int /*<<< orphan*/  bd_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bd_get_disc_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bd_get_title_info (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int bd_get_titles (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bd_open (char const*,int /*<<< orphan*/ *) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hb_log (char*) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int /*<<< orphan*/  title_info_compare_mpls ; 

hb_bd_t * hb_bd_init( hb_handle_t *h, const char * path )
{
    hb_bd_t * d;
    int ii;

    d = calloc( sizeof( hb_bd_t ), 1 );
    d->h = h;

    /* Open device */
    d->bd = bd_open( path, NULL );
    if( d->bd == NULL )
    {
        /*
         * Not an error, may be a stream - which we'll try in a moment.
         */
        hb_log( "bd: not a bd - trying as a stream/file instead" );
        goto fail;
    }

    d->title_count = bd_get_titles( d->bd, TITLES_RELEVANT, 0 );
    if ( d->title_count == 0 )
    {
        hb_log( "bd: not a bd - trying as a stream/file instead" );
        goto fail;
    }
    d->title_info = calloc( sizeof( BLURAY_TITLE_INFO* ) , d->title_count );
    for ( ii = 0; ii < d->title_count; ii++ )
    {
        d->title_info[ii] = bd_get_title_info( d->bd, ii, 0 );
    }
    qsort(d->title_info, d->title_count, sizeof( BLURAY_TITLE_INFO* ), title_info_compare_mpls );
    d->disc_info = bd_get_disc_info(d->bd);
    d->path = strdup( path );

    return d;

fail:
    if( d->bd ) bd_close( d->bd );
    free( d );
    return NULL;
}