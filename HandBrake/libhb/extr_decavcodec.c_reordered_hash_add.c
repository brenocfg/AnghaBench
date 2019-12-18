#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int sequence; } ;
typedef  TYPE_1__ reordered_data_t ;
struct TYPE_7__ {TYPE_1__** reordered_hash; } ;
typedef  TYPE_2__ hb_work_private_t ;

/* Variables and functions */
 int REORDERED_HASH_MASK ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void
reordered_hash_add(hb_work_private_t * pv, reordered_data_t * reordered)
{
    int slot = reordered->sequence & REORDERED_HASH_MASK;

    // Free any unused previous entries.
    // This can happen due to libav parser feeding partial
    // frames data to the decoder.
    // It can also happen due to decoding errors.
    free(pv->reordered_hash[slot]);
    pv->reordered_hash[slot] = reordered;
}