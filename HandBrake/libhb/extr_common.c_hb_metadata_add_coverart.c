#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/ * list_coverart; } ;
typedef  TYPE_1__ hb_metadata_t ;
struct TYPE_7__ {int size; int type; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ hb_coverart_t ;

/* Variables and functions */
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  hb_list_add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * hb_list_init () ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

void hb_metadata_add_coverart( hb_metadata_t *metadata, const uint8_t *data, int size, int type )
{
    if ( metadata )
    {
        if ( metadata->list_coverart == NULL )
        {
            metadata->list_coverart = hb_list_init();
        }
        hb_coverart_t *art = calloc( 1, sizeof(hb_coverart_t) );
        art->data = malloc( size );
        memcpy( art->data, data, size );
        art->size = size;
        art->type = type;
        hb_list_add( metadata->list_coverart, art );
    }
}