#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ data; } ;
struct TYPE_4__ {TYPE_3__** pps_list; int /*<<< orphan*/  const* pps; } ;
typedef  TYPE_1__ HEVCParamSets ;
typedef  int /*<<< orphan*/  HEVCPPS ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_unref (TYPE_3__**) ; 

__attribute__((used)) static void remove_pps(HEVCParamSets *s, int id)
{
    if (s->pps_list[id] && s->pps == (const HEVCPPS*)s->pps_list[id]->data)
        s->pps = NULL;
    av_buffer_unref(&s->pps_list[id]);
}