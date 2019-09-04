#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int length; } ;
typedef  TYPE_1__ HuffTable ;

/* Variables and functions */

__attribute__((used)) static int compare_by_length(const void *a, const void *b)
{
    HuffTable a_val = *(HuffTable *) a;
    HuffTable b_val = *(HuffTable *) b;
    return a_val.length - b_val.length;
}