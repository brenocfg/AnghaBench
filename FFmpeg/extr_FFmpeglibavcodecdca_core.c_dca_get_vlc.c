#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int offset; int /*<<< orphan*/  max_depth; TYPE_1__* vlc; } ;
struct TYPE_4__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  table; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ DCAVLC ;

/* Variables and functions */
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dca_get_vlc(GetBitContext *s, DCAVLC *v, int i)
{
    return get_vlc2(s, v->vlc[i].table, v->vlc[i].bits, v->max_depth) + v->offset;
}