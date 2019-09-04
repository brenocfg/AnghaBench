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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {char const* name; } ;

/* Variables and functions */
 int const CCV_NNC_BACKEND_COUNT ; 
 scalar_t__ const CCV_NNC_NO_BACKEND ; 
 int _ccv_nnc_cmd_backend_ph (scalar_t__ const) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* backend_init_map ; 

const char* ccv_nnc_cmd_backend_name(const uint32_t backend)
{
	if (backend == CCV_NNC_NO_BACKEND)
		return "CCV_NNC_NO_BACKEND";
	const int idx = _ccv_nnc_cmd_backend_ph(backend);
	assert(idx >= 0);
	assert(idx < CCV_NNC_BACKEND_COUNT);
	return backend_init_map[idx].name;
}