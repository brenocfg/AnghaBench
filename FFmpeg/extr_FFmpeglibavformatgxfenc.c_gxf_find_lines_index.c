#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ height; int /*<<< orphan*/  index; } ;
struct TYPE_8__ {TYPE_1__* codecpar; TYPE_2__* priv_data; } ;
struct TYPE_7__ {int /*<<< orphan*/  lines_index; } ;
struct TYPE_6__ {scalar_t__ height; } ;
typedef  TYPE_2__ GXFStreamContext ;
typedef  TYPE_3__ AVStream ;

/* Variables and functions */
 TYPE_4__* gxf_lines_tab ; 

__attribute__((used)) static int gxf_find_lines_index(AVStream *st)
{
    GXFStreamContext *sc = st->priv_data;
    int i;

    for (i = 0; i < 6; ++i) {
        if (st->codecpar->height == gxf_lines_tab[i].height) {
            sc->lines_index = gxf_lines_tab[i].index;
            return 0;
        }
    }
    return -1;
}