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
struct TYPE_7__ {int spatial_decomposition_count; TYPE_2__* plane; int /*<<< orphan*/  header_state; int /*<<< orphan*/  c; int /*<<< orphan*/  nb_planes; } ;
struct TYPE_6__ {TYPE_1__** band; } ;
struct TYPE_5__ {int /*<<< orphan*/  qlog; } ;
typedef  TYPE_3__ SnowContext ;

/* Variables and functions */
 int FFMIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void encode_qlogs(SnowContext *s){
    int plane_index, level, orientation;

    for(plane_index=0; plane_index<FFMIN(s->nb_planes, 2); plane_index++){
        for(level=0; level<s->spatial_decomposition_count; level++){
            for(orientation=level ? 1:0; orientation<4; orientation++){
                if(orientation==2) continue;
                put_symbol(&s->c, s->header_state, s->plane[plane_index].band[level][orientation].qlog, 1);
            }
        }
    }
}