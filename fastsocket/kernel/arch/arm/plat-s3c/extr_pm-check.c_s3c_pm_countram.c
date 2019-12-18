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
typedef  int u32 ;
struct resource {scalar_t__ end; scalar_t__ start; } ;

/* Variables and functions */
 int CHECK_CHUNKSIZE ; 
 int /*<<< orphan*/  S3C_PMDBG (char*,unsigned long,unsigned long,int) ; 

__attribute__((used)) static u32 *s3c_pm_countram(struct resource *res, u32 *val)
{
	u32 size = (u32)(res->end - res->start)+1;

	size += CHECK_CHUNKSIZE-1;
	size /= CHECK_CHUNKSIZE;

	S3C_PMDBG("Area %08lx..%08lx, %d blocks\n",
		  (unsigned long)res->start, (unsigned long)res->end, size);

	*val += size * sizeof(u32);
	return val;
}