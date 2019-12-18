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
typedef  scalar_t__ UINT8 ;
typedef  size_t UINT16 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 size_t MAX_UUID_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__* sdp_base_uuid ; 

BOOLEAN sdpu_is_base_uuid (UINT8 *p_uuid)
{
    UINT16    xx;

    for (xx = 4; xx < MAX_UUID_SIZE; xx++)
        if (p_uuid[xx] != sdp_base_uuid[xx]) {
            return (FALSE);
        }

    /* If here, matched */
    return (TRUE);
}