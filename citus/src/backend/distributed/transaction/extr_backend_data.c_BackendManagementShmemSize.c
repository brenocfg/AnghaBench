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
typedef  size_t Size ;
typedef  int /*<<< orphan*/  BackendManagementShmemData ;
typedef  int /*<<< orphan*/  BackendData ;

/* Variables and functions */
 int TotalProcCount () ; 
 size_t add_size (size_t,int) ; 
 int mul_size (int,int) ; 

__attribute__((used)) static size_t
BackendManagementShmemSize(void)
{
	Size size = 0;
	int totalProcs = TotalProcCount();

	size = add_size(size, sizeof(BackendManagementShmemData));
	size = add_size(size, mul_size(sizeof(BackendData), totalProcs));

	return size;
}