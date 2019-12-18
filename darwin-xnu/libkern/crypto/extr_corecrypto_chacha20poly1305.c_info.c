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
struct ccchacha20poly1305_info {int dummy; } ;
struct TYPE_2__ {struct ccchacha20poly1305_info const* (* info ) () ;} ;

/* Variables and functions */
 TYPE_1__* fns () ; 
 struct ccchacha20poly1305_info const* stub1 () ; 

__attribute__((used)) static const struct ccchacha20poly1305_info *info(void)
{
    return fns()->info();
}