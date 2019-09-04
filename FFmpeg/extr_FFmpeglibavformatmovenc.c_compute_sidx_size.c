#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* priv_data; } ;
struct TYPE_7__ {int nb_streams; TYPE_1__* tracks; } ;
struct TYPE_6__ {int data_offset; } ;
typedef  TYPE_2__ MOVMuxContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int get_sidx_size (TYPE_3__*) ; 

__attribute__((used)) static int compute_sidx_size(AVFormatContext *s)
{
    int i, sidx_size;
    MOVMuxContext *mov = s->priv_data;

    sidx_size = get_sidx_size(s);
    if (sidx_size < 0)
        return sidx_size;

    for (i = 0; i < mov->nb_streams; i++)
        mov->tracks[i].data_offset += sidx_size;

    return sidx_size;
}