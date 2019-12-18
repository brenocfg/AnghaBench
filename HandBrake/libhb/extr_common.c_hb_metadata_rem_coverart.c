#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  list_coverart; } ;
typedef  TYPE_1__ hb_metadata_t ;
struct TYPE_8__ {struct TYPE_8__* data; } ;
typedef  TYPE_2__ hb_coverart_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* hb_list_item (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hb_list_rem (int /*<<< orphan*/ ,TYPE_2__*) ; 

void hb_metadata_rem_coverart( hb_metadata_t *metadata, int idx )
{
    if ( metadata )
    {
        hb_coverart_t *art = hb_list_item( metadata->list_coverart, idx );
        if ( art )
        {
            hb_list_rem( metadata->list_coverart, art );
            free( art->data );
            free( art );
        }
    }
}