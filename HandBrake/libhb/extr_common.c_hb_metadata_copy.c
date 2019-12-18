#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ list_coverart; void* long_description; void* description; void* genre; void* album; void* comment; void* release_date; void* composer; void* album_artist; void* artist; void* name; } ;
typedef  TYPE_1__ hb_metadata_t ;
struct TYPE_9__ {int /*<<< orphan*/  type; int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ hb_coverart_t ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 
 int hb_list_count (scalar_t__) ; 
 TYPE_2__* hb_list_item (scalar_t__,int) ; 
 int /*<<< orphan*/  hb_metadata_add_coverart (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* strdup (void*) ; 

hb_metadata_t *hb_metadata_copy( const hb_metadata_t *src )
{
    hb_metadata_t *metadata = NULL;

    if ( src )
    {
        metadata = calloc( 1, sizeof(*metadata) );
        if ( src->name )
        {
            metadata->name = strdup(src->name);
        }
        if ( src->artist )
        {
            metadata->artist = strdup(src->artist);
        }
        if ( src->album_artist )
        {
            metadata->album_artist = strdup(src->album_artist);
        }
        if ( src->composer )
        {
            metadata->composer = strdup(src->composer);
        }
        if ( src->release_date )
        {
            metadata->release_date = strdup(src->release_date);
        }
        if ( src->comment )
        {
            metadata->comment = strdup(src->comment);
        }
        if ( src->album )
        {
            metadata->album = strdup(src->album);
        }
        if ( src->genre )
        {
            metadata->genre = strdup(src->genre);
        }
        if ( src->description )
        {
            metadata->description = strdup(src->description);
        }
        if ( src->long_description )
        {
            metadata->long_description = strdup(src->long_description);
        }
        if ( src->list_coverart )
        {
            int ii;
            for ( ii = 0; ii < hb_list_count( src->list_coverart ); ii++ )
            {
                hb_coverart_t *art = hb_list_item( src->list_coverart, ii );
                hb_metadata_add_coverart(
                        metadata, art->data, art->size, art->type );
            }
        }
    }
    return metadata;
}