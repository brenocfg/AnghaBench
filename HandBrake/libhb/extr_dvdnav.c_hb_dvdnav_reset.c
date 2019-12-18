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
struct TYPE_3__ {scalar_t__ dvdnav; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ hb_dvdnav_t ;

/* Variables and functions */
 scalar_t__ DVDNAV_STATUS_OK ; 
 int /*<<< orphan*/  DVD_READ_CACHE ; 
 int /*<<< orphan*/  dvdnav_close (scalar_t__) ; 
 int /*<<< orphan*/  dvdnav_err_to_string (scalar_t__) ; 
 scalar_t__ dvdnav_open (scalar_t__*,char*) ; 
 scalar_t__ dvdnav_set_PGC_positioning_flag (scalar_t__,int) ; 
 scalar_t__ dvdnav_set_readahead_flag (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hb_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_log (char*) ; 
 char* hb_utf8_to_cp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hb_dvdnav_reset( hb_dvdnav_t * d )
{
    char * path_ccp = hb_utf8_to_cp( d->path );
    if ( d->dvdnav )
        dvdnav_close( d->dvdnav );

    /* Open device */
    if( dvdnav_open(&d->dvdnav, path_ccp) != DVDNAV_STATUS_OK )
    {
        /*
         * Not an error, may be a stream - which we'll try in a moment.
         */
        hb_log( "dvd: not a dvd - trying as a stream/file instead" );
        goto fail;
    }

    if (dvdnav_set_readahead_flag(d->dvdnav, DVD_READ_CACHE) !=
        DVDNAV_STATUS_OK)
    {
        hb_error("Error: dvdnav_set_readahead_flag: %s\n",
                 dvdnav_err_to_string(d->dvdnav));
        goto fail;
    }

    /*
     ** set the PGC positioning flag to have position information
     ** relatively to the whole feature instead of just relatively to the
     ** current chapter
     **/
    if (dvdnav_set_PGC_positioning_flag(d->dvdnav, 1) != DVDNAV_STATUS_OK)
    {
        hb_error("Error: dvdnav_set_PGC_positioning_flag: %s\n",
                 dvdnav_err_to_string(d->dvdnav));
        goto fail;
    }

    free( path_ccp );

    return 1;

fail:
    if( d->dvdnav ) dvdnav_close( d->dvdnav );
    free( path_ccp );
    return 0;
}