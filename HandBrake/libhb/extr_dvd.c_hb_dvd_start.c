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
typedef  int /*<<< orphan*/  hb_title_t ;
typedef  int /*<<< orphan*/  hb_dvd_t ;
struct TYPE_2__ {int (* start ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 TYPE_1__* dvd_methods ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int hb_dvd_start( hb_dvd_t * d, hb_title_t *title, int chapter )
{
    return dvd_methods->start(d, title, chapter);
}