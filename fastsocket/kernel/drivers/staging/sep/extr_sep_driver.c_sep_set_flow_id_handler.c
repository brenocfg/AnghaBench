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
struct sep_flow_context_t {unsigned long flow_id; } ;
struct sep_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SEP_TEMP_FLOW_ID ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sep_flow_context_t* sep_find_flow_context (struct sep_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sep_mutex ; 

__attribute__((used)) static int sep_set_flow_id_handler(struct sep_device *sep,
						unsigned long flow_id)
{
	int error = 0;
	struct sep_flow_context_t *flow_data_ptr;

	/* find the flow data structure that was just used for creating new flow
	   - its id should be default */

	mutex_lock(&sep_mutex);
	flow_data_ptr = sep_find_flow_context(sep, SEP_TEMP_FLOW_ID);
	if (flow_data_ptr)
		flow_data_ptr->flow_id = flow_id;	/* set flow id */
	else
		error = -EINVAL;
	mutex_unlock(&sep_mutex);
	return error;
}