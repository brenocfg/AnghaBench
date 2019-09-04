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
struct TYPE_2__ {int /*<<< orphan*/  context; int /*<<< orphan*/  (* data_deinit ) (void* const,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ ccv_cnnp_dataframe_reducer_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/  (*) (void* const,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  stub1 (void* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _ccv_cnnp_reducer_data_deinit(void* const data, void* const context)
{
	ccv_cnnp_dataframe_reducer_t* const reducer = (ccv_cnnp_dataframe_reducer_t*)context;
	assert(reducer->data_deinit);
	reducer->data_deinit(data, reducer->context);
}