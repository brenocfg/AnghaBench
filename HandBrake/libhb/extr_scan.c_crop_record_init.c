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
struct TYPE_3__ {void* r; void* l; void* b; void* t; } ;
typedef  TYPE_1__ crop_record_t ;

/* Variables and functions */
 void* calloc (int,int) ; 

__attribute__((used)) static crop_record_t * crop_record_init( int max_previews )
{
    crop_record_t *crops = calloc( 1, sizeof(*crops) );

    crops->t = calloc( max_previews, sizeof(int) );
    crops->b = calloc( max_previews, sizeof(int) );
    crops->l = calloc( max_previews, sizeof(int) );
    crops->r = calloc( max_previews, sizeof(int) );

    return crops;
}