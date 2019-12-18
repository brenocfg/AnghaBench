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
typedef  int /*<<< orphan*/  box ;

/* Variables and functions */
 float box_intersection (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float box_union (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

float box_iou(box a, box b)
{
    return box_intersection(a, b)/box_union(a, b);
}