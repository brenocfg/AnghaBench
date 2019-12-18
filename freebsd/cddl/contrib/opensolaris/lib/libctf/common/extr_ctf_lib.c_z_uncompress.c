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
typedef  int /*<<< orphan*/  ulong_t ;
struct TYPE_2__ {int (* z_uncompress ) (void*,int /*<<< orphan*/ *,void const*,size_t) ;} ;

/* Variables and functions */
 int stub1 (void*,int /*<<< orphan*/ *,void const*,size_t) ; 
 TYPE_1__ zlib ; 

int
z_uncompress(void *dst, size_t *dstlen, const void *src, size_t srclen)
{
	return (zlib.z_uncompress(dst, (ulong_t *)dstlen, src, srclen));
}