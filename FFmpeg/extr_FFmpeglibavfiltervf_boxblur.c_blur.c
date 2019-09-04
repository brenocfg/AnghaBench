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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  blur16 (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int,int,int) ; 
 int /*<<< orphan*/  blur8 (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int,int,int) ; 

__attribute__((used)) static inline void blur(uint8_t *dst, int dst_step, const uint8_t *src, int src_step,
                        int len, int radius, int pixsize)
{
    if (pixsize == 1) blur8 (dst, dst_step   , src, src_step   , len, radius);
    else              blur16((uint16_t*)dst, dst_step>>1, (const uint16_t*)src, src_step>>1, len, radius);
}