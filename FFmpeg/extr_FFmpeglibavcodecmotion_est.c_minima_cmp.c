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
struct TYPE_2__ {int height; } ;
typedef  TYPE_1__ Minima ;

/* Variables and functions */

__attribute__((used)) static int minima_cmp(const void *a, const void *b){
    const Minima *da = (const Minima *) a;
    const Minima *db = (const Minima *) b;

    return da->height - db->height;
}