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
typedef  int kxld_size_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  s_cross_link_enabled ; 
 int s_cross_link_page_size ; 

boolean_t kxld_set_cross_link_page_size(kxld_size_t target_page_size)
{
    // verify radix 2
    if ((target_page_size != 0) && 
        ((target_page_size & (target_page_size - 1)) == 0)) {

        s_cross_link_enabled = TRUE;
        s_cross_link_page_size = target_page_size;

        return TRUE;   
    } else {
        return FALSE;
    }
}