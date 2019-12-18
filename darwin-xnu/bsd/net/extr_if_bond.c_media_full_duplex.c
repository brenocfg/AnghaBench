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
struct media_info {int mi_active; } ;

/* Variables and functions */
 int IFM_FDX ; 

__attribute__((used)) static __inline__ int
media_full_duplex(const struct media_info * mi)
{
    return ((mi->mi_active & IFM_FDX) != 0);
}