#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned char* u8; double* f64; } ;
struct TYPE_8__ {int cols; int rows; int step; TYPE_1__ data; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ ccv_dense_matrix_t ;

/* Variables and functions */
 int CCV_GET_CHANNEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_zero (TYPE_2__*) ; 

__attribute__((used)) static void naive_ssd(ccv_dense_matrix_t* image, ccv_dense_matrix_t* template, ccv_dense_matrix_t* out)
{
	int thw = template->cols / 2;
	int thh = template->rows / 2;
	int i, j, k, x, y, ch = CCV_GET_CHANNEL(image->type);
	unsigned char* i_ptr = image->data.u8 + thh * image->step;
	double* o = out->data.f64 + out->cols * thh;
	ccv_zero(out);
	for (i = thh; i < image->rows - thh - 1; i++)
	{
		for (j = thw; j < image->cols - thw - 1; j++)
		{
			unsigned char* t_ptr = template->data.u8;
			unsigned char* j_ptr = i_ptr - thh * image->step;
			o[j] = 0;
			for (y = -thh; y <= thh; y++)
			{
				for (x = -thw; x <= thw; x++)
					for (k = 0; k < ch; k++)
						o[j] += (j_ptr[(x + j) * ch + k] - t_ptr[(x + thw) * ch + k]) * (j_ptr[(x + j) * ch + k] - t_ptr[(x + thw) * ch + k]);
				t_ptr += template->step;
				j_ptr += image->step;
			}
		}
		i_ptr += image->step;
		o += out->cols;
	}
}