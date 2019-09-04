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
struct media_info {int mi_status; } ;

/* Variables and functions */
 int IFM_ACTIVE ; 
 int IFM_AVALID ; 

__attribute__((used)) static __inline__ int
media_active(const struct media_info * mi)
{
    if ((mi->mi_status & IFM_AVALID) == 0) {
	return (1);
    }
    return ((mi->mi_status & IFM_ACTIVE) != 0);
}