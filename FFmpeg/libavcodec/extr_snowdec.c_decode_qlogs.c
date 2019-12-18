#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nb_planes; int spatial_decomposition_count; TYPE_2__* plane; int /*<<< orphan*/  header_state; int /*<<< orphan*/  c; } ;
struct TYPE_6__ {TYPE_1__** band; } ;
struct TYPE_5__ {int qlog; } ;
typedef  TYPE_3__ SnowContext ;

/* Variables and functions */
 int get_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void decode_qlogs(SnowContext *s){
    int plane_index, level, orientation;

    for(plane_index=0; plane_index < s->nb_planes; plane_index++){
        for(level=0; level<s->spatial_decomposition_count; level++){
            for(orientation=level ? 1:0; orientation<4; orientation++){
                int q;
                if     (plane_index==2) q= s->plane[1].band[level][orientation].qlog;
                else if(orientation==2) q= s->plane[plane_index].band[level][1].qlog;
                else                    q= get_symbol(&s->c, s->header_state, 1);
                s->plane[plane_index].band[level][orientation].qlog= q;
            }
        }
    }
}