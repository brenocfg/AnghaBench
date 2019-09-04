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

/* Variables and functions */
 int /*<<< orphan*/  store8 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void lz4_fill16(uint8_t * ptr)
{
  store8(ptr,-1);
  store8(ptr+8,-1);
}