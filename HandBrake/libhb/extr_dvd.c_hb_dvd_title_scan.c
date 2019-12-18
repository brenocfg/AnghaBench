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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  hb_title_t ;
typedef  int /*<<< orphan*/  hb_dvd_t ;
struct TYPE_2__ {int /*<<< orphan*/ * (* title_scan ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* dvd_methods ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

hb_title_t * hb_dvd_title_scan( hb_dvd_t * d, int t, uint64_t min_duration )
{
    return dvd_methods->title_scan(d, t, min_duration);
}