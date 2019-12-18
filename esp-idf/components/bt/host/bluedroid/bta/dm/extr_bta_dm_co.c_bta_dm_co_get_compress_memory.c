#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ ** tBTA_SYS_ID ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/ * UINT32 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ **) ; 

BOOLEAN bta_dm_co_get_compress_memory(tBTA_SYS_ID id, UINT8 **memory_p, UINT32 *memory_size)
{
    UNUSED(id);
    UNUSED(memory_p);
    UNUSED(memory_size);
    return TRUE;
}