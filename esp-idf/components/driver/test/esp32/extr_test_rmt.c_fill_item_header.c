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
typedef  int /*<<< orphan*/  rmt_item32_t ;

/* Variables and functions */
 int /*<<< orphan*/  HEADER_HIGH_US ; 
 int /*<<< orphan*/  HEADER_LOW_US ; 
 int /*<<< orphan*/  fill_item_level (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fill_item_header(rmt_item32_t* item)
{
    fill_item_level(item, HEADER_HIGH_US, HEADER_LOW_US);
}