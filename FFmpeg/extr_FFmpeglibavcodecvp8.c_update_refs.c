#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* update_altref; void* update_golden; int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ VP8Context ;
typedef  int /*<<< orphan*/  VP56RangeCoder ;

/* Variables and functions */
 int /*<<< orphan*/  VP56_FRAME_GOLDEN ; 
 int /*<<< orphan*/  VP56_FRAME_GOLDEN2 ; 
 void* ref_to_update (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int vp8_rac_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_refs(VP8Context *s)
{
    VP56RangeCoder *c = &s->c;

    int update_golden = vp8_rac_get(c);
    int update_altref = vp8_rac_get(c);

    s->update_golden = ref_to_update(s, update_golden, VP56_FRAME_GOLDEN);
    s->update_altref = ref_to_update(s, update_altref, VP56_FRAME_GOLDEN2);
}