#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  unused ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  dvd_reader_t ;

/* Variables and functions */
 int /*<<< orphan*/  DVDClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DVDOpen (char*) ; 
 scalar_t__ DVDUDFVolumeInfo (int /*<<< orphan*/ *,char*,int,unsigned char*,int) ; 

__attribute__((used)) static char * hb_dvdnav_name( char * path )
{
    static char name[1024];
    unsigned char unused[1024];
    dvd_reader_t * reader;

    reader = DVDOpen( path );
    if( !reader )
    {
        return NULL;
    }

    if( DVDUDFVolumeInfo( reader, name, sizeof( name ),
                          unused, sizeof( unused ) ) )
    {
        DVDClose( reader );
        return NULL;
    }

    DVDClose( reader );
    return name;
}