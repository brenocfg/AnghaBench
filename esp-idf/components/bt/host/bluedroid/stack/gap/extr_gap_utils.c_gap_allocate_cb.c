#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* p_data; scalar_t__ index; scalar_t__ in_use; } ;
typedef  TYPE_1__ tGAP_INFO ;
typedef  scalar_t__ UINT8 ;
struct TYPE_6__ {TYPE_1__* blk; } ;

/* Variables and functions */
 scalar_t__ GAP_MAX_BLOCKS ; 
 scalar_t__ TRUE ; 
 TYPE_3__ gap_cb ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

tGAP_INFO *gap_allocate_cb (void)
{
    tGAP_INFO     *p_cb = &gap_cb.blk[0];
    UINT8        x;

    for (x = 0; x < GAP_MAX_BLOCKS; x++, p_cb++) {
        if (!p_cb->in_use) {
            memset (p_cb, 0, sizeof (tGAP_INFO));

            p_cb->in_use = TRUE;
            p_cb->index = x;
            p_cb->p_data = (void *)NULL;
            return (p_cb);
        }
    }

    /* If here, no free control blocks found */
    return (NULL);
}