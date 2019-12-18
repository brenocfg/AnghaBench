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
struct wps_sm {int dummy; } ;

/* Variables and functions */
 struct wps_sm* gWpsSm ; 

struct wps_sm *
wps_sm_get(void)
{
    return gWpsSm;
}