#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  d; } ;
typedef  TYPE_1__ ccv_nnc_tensor_ref_t ;
struct TYPE_5__ {int /*<<< orphan*/  c; int /*<<< orphan*/ * const ref_version; } ;
typedef  TYPE_2__ ccv_nnc_autograd_tensor_version_t ;
typedef  int /*<<< orphan*/  ccv_nnc_autograd_tensor_symbol_t ;
typedef  int /*<<< orphan*/  ccv_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ * const) ; 
 scalar_t__ ccv_array_get (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ccv_nnc_autograd_tensor_symbol_t* _ccv_nnc_autograd_tensor_symbol_from_tensor_version(ccv_array_t* const autograd_tensor_symbols, const ccv_nnc_autograd_tensor_version_t* const tensor_ver)
{
	assert(tensor_ver->ref_version);
	const ccv_nnc_tensor_ref_t* const tensor_ref = (ccv_nnc_tensor_ref_t*)ccv_array_get(tensor_ver->ref_version, tensor_ver->c);
	return (ccv_nnc_autograd_tensor_symbol_t*)ccv_array_get(autograd_tensor_symbols, tensor_ref->d);
}