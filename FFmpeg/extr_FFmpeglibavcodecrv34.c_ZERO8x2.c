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
typedef  void uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  fill_rectangle (void*,int,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void ZERO8x2(void* dst, int stride)
{
    fill_rectangle(dst,                 1, 2, stride, 0, 4);
    fill_rectangle(((uint8_t*)(dst))+4, 1, 2, stride, 0, 4);
}