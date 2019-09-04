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

/* Variables and functions */
 int /*<<< orphan*/  ccv_array_free_immediately ; 
 int /*<<< orphan*/  ccv_cache ; 
 int /*<<< orphan*/  ccv_cache_init (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ccv_cache_opt ; 
 int /*<<< orphan*/  ccv_matrix_free_immediately ; 

void ccv_enable_cache(size_t size)
{
	ccv_cache_opt = 1;
	ccv_cache_init(&ccv_cache, size, 2, ccv_matrix_free_immediately, ccv_array_free_immediately);
}