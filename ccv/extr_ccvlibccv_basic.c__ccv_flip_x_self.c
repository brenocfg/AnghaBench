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
struct TYPE_4__ {unsigned char* u8; } ;
struct TYPE_5__ {int rows; int cols; int /*<<< orphan*/  step; TYPE_1__ data; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ ccv_dense_matrix_t ;

/* Variables and functions */
 int CCV_GET_CHANNEL (int /*<<< orphan*/ ) ; 
 int CCV_GET_DATA_TYPE_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ alloca (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static void _ccv_flip_x_self(ccv_dense_matrix_t* a)
{
	int i, j;
	int len = CCV_GET_DATA_TYPE_SIZE(a->type) * CCV_GET_CHANNEL(a->type);
	unsigned char* buffer = (unsigned char*)alloca(len);
	unsigned char* a_ptr = a->data.u8;
	for (i = 0; i < a->rows; i++)
	{
		for (j = 0; j < a->cols / 2; j++)
		{
			memcpy(buffer, a_ptr + j * len, len);
			memcpy(a_ptr + j * len, a_ptr + (a->cols - 1 - j) * len, len);
			memcpy(a_ptr + (a->cols - 1 - j) * len, buffer, len);
		}
		a_ptr += a->step;
	}
}