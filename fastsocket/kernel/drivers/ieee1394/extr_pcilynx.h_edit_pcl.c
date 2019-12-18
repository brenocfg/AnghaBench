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
struct ti_pcl {int dummy; } ;
struct ti_lynx {struct ti_pcl* pcl_mem; } ;
typedef  int /*<<< orphan*/  pcltmp_t ;
typedef  int pcl_t ;

/* Variables and functions */

__attribute__((used)) static inline struct ti_pcl *edit_pcl(const struct ti_lynx *lynx, pcl_t pclid,
                                      pcltmp_t *tmp)
{
        return lynx->pcl_mem + pclid * sizeof(struct ti_pcl);
}