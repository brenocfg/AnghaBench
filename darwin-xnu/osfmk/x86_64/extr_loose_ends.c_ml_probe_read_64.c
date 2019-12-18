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
typedef  int /*<<< orphan*/  pmap_paddr_t ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int addr64_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int PAGE_MASK ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 unsigned int ml_phys_read_64 (int /*<<< orphan*/ ) ; 

boolean_t 
ml_probe_read_64(addr64_t paddr64, unsigned int *val)
{
    if ((PAGE_SIZE - (paddr64 & PAGE_MASK)) < 4)
        return FALSE;

    *val = ml_phys_read_64((pmap_paddr_t)paddr64);
    return TRUE;
}