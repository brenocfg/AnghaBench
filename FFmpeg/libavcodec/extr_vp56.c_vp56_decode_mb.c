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
typedef  int /*<<< orphan*/  VP56mb ;
struct TYPE_8__ {int (* parse_coeff ) (TYPE_2__*) ;TYPE_1__** frames; } ;
typedef  TYPE_2__ VP56Context ;
struct TYPE_7__ {scalar_t__ key_frame; } ;

/* Variables and functions */
 size_t VP56_FRAME_CURRENT ; 
 int /*<<< orphan*/  VP56_MB_INTRA ; 
 int stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  vp56_decode_mv (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  vp56_render_mb (TYPE_2__*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vp56_decode_mb(VP56Context *s, int row, int col, int is_alpha)
{
    VP56mb mb_type;
    int ret;

    if (s->frames[VP56_FRAME_CURRENT]->key_frame)
        mb_type = VP56_MB_INTRA;
    else
        mb_type = vp56_decode_mv(s, row, col);

    ret = s->parse_coeff(s);
    if (ret < 0)
        return ret;

    vp56_render_mb(s, row, col, is_alpha, mb_type);

    return 0;
}