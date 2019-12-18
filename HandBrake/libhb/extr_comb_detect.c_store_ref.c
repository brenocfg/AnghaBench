#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ ** ref_used; int /*<<< orphan*/ ** ref; } ;
typedef  TYPE_1__ hb_filter_private_t ;
typedef  int /*<<< orphan*/  hb_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_buffer_close (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static void store_ref(hb_filter_private_t * pv, hb_buffer_t * b)
{
    // Free unused buffer
    if (!pv->ref_used[0])
    {
        hb_buffer_close(&pv->ref[0]);
    }
    memmove(&pv->ref[0],      &pv->ref[1],      sizeof(pv->ref[0])      * 2 );
    memmove(&pv->ref_used[0], &pv->ref_used[1], sizeof(pv->ref_used[0]) * 2 );
    pv->ref[2]      = b;
    pv->ref_used[2] = 0;
}