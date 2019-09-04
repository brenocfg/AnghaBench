#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* isa; } ;
typedef  TYPE_2__ ccv_cnnp_model_t ;
typedef  int /*<<< orphan*/  ccv_array_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* add_to_output ) (TYPE_2__* const,int /*<<< orphan*/ * const) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__* const,int /*<<< orphan*/ * const) ; 

__attribute__((used)) static inline void ccv_cnnp_model_add_to_output(ccv_cnnp_model_t* const self, ccv_array_t* const outputs)
{
	if (self->isa->add_to_output)
		self->isa->add_to_output(self, outputs);
}