#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ kind_t ;
struct TYPE_7__ {TYPE_1__* list; } ;
struct TYPE_8__ {TYPE_2__ pes; } ;
typedef  TYPE_3__ hb_stream_t ;
struct TYPE_9__ {scalar_t__ kind; } ;
struct TYPE_6__ {size_t stream_type; scalar_t__ stream_kind; } ;

/* Variables and functions */
 scalar_t__ N ; 
 scalar_t__ U ; 
 TYPE_5__* st2codec ; 

__attribute__((used)) static void update_pes_kind( hb_stream_t * stream, int idx )
{
    kind_t kind = st2codec[stream->pes.list[idx].stream_type].kind;
    if ( kind != U && kind != N )
    {
        stream->pes.list[idx].stream_kind = kind;
    }
}