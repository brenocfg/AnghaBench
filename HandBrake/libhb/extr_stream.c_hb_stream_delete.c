#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* list; } ;
struct TYPE_7__ {TYPE_3__* list; } ;
struct TYPE_9__ {struct TYPE_9__* path; TYPE_2__ pes; TYPE_1__ ts; } ;
typedef  TYPE_3__ hb_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  hb_stream_delete_dynamic (TYPE_3__*) ; 

__attribute__((used)) static void hb_stream_delete( hb_stream_t *d )
{
    hb_stream_delete_dynamic( d );
    free( d->ts.list );
    free( d->pes.list );
    free( d->path );
    free( d );
}