#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int rows; int /*<<< orphan*/  cols; int /*<<< orphan*/ * vals; } ;
struct TYPE_5__ {TYPE_1__ X; } ;
typedef  TYPE_2__ data ;

/* Variables and functions */
 int /*<<< orphan*/  scale_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 

void scale_data_rows(data d, float s)
{
    int i;
    for(i = 0; i < d.X.rows; ++i){
        scale_array(d.X.vals[i], d.X.cols, s);
    }
}