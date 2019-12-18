#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int rnum; } ;
typedef  TYPE_1__ ccv_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccv_array_resize (TYPE_1__* const,int) ; 

__attribute__((used)) static int _ccv_nnc_tensor_metadata_pos_new(ccv_array_t* const tensor_metadata, const size_t size)
{
	int pos = tensor_metadata->rnum;
	int rsize = (size + 15) / 16;
	ccv_array_resize(tensor_metadata, pos + rsize);
	return (pos << 1) + 1;
}