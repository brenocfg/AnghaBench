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
typedef  int /*<<< orphan*/  hb_title_t ;

/* Variables and functions */
 int /*<<< orphan*/  h_scan ; 
 int /*<<< orphan*/  const* lookup_title (int /*<<< orphan*/ ,int,int*) ; 

const hb_title_t*
ghb_lookup_title(int title_id, int *index)
{
    return lookup_title(h_scan, title_id, index);
}