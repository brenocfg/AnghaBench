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
typedef  int /*<<< orphan*/  unpack_user ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int unpack_callback_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int unpack_callback_uint32(unpack_user* u, uint32_t d)
{
    return unpack_callback_uint64(u, d);
}