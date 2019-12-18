#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t w; size_t size; size_t n; scalar_t__ h; } ;
typedef  TYPE_1__ layer ;

/* Variables and functions */

__attribute__((used)) static size_t get_workspace_size(layer l){
    return (size_t)l.h*l.w*l.size*l.size*l.n*sizeof(float);
}