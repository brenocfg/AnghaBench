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
typedef  int /*<<< orphan*/  u32 ;
struct ti_pcl {int dummy; } ;
struct ti_lynx {scalar_t__ pcl_mem; } ;
typedef  int pcl_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy_le32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void get_pcl(const struct ti_lynx *lynx, pcl_t pclid,
                           struct ti_pcl *pcl)
{
        memcpy_le32((u32 *)pcl,
                    (u32 *)(lynx->pcl_mem + pclid * sizeof(struct ti_pcl)),
                    sizeof(struct ti_pcl));
}