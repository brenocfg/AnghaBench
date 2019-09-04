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
typedef  int /*<<< orphan*/  cl_mem_flags ;

/* Variables and functions */
 int AV_HWFRAME_MAP_READ ; 
 int AV_HWFRAME_MAP_WRITE ; 
 int /*<<< orphan*/  CL_MEM_READ_ONLY ; 
 int /*<<< orphan*/  CL_MEM_READ_WRITE ; 
 int /*<<< orphan*/  CL_MEM_WRITE_ONLY ; 

__attribute__((used)) static inline cl_mem_flags opencl_mem_flags_for_mapping(int map_flags)
{
    if ((map_flags & AV_HWFRAME_MAP_READ) &&
        (map_flags & AV_HWFRAME_MAP_WRITE))
        return CL_MEM_READ_WRITE;
    else if (map_flags & AV_HWFRAME_MAP_READ)
        return CL_MEM_READ_ONLY;
    else if (map_flags & AV_HWFRAME_MAP_WRITE)
        return CL_MEM_WRITE_ONLY;
    else
        return 0;
}