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
struct TYPE_2__ {int key; } ;
typedef  TYPE_1__ TiffGeoTagKeyName ;

/* Variables and functions */

__attribute__((used)) static int cmp_id_key(const void *id, const void *k)
{
    return *(const int*)id - ((const TiffGeoTagKeyName*)k)->key;
}