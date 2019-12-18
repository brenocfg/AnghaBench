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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ KHDISPATCH_WORKSPACE_SIZE ; 
 int khrn_platform_malloc (scalar_t__,char*) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int workspace ; 

__attribute__((used)) static void check_workspace(uint32_t size)
{
   /* todo: find a better way to handle scatter/gather bulks */
   vcos_assert(size <= KHDISPATCH_WORKSPACE_SIZE);
   if (!workspace) {
      workspace = khrn_platform_malloc(KHDISPATCH_WORKSPACE_SIZE, "rpc_workspace");
      vcos_assert(workspace);
   }
}