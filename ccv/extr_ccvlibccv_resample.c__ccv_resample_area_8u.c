#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int di; int si; unsigned int alpha; } ;
typedef  TYPE_2__ ccv_int_alpha ;
struct TYPE_6__ {unsigned char* u8; } ;
struct TYPE_8__ {int cols; double rows; int step; TYPE_1__ data; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ ccv_dense_matrix_t ;

/* Variables and functions */
 unsigned int CCV_GET_CHANNEL (int /*<<< orphan*/ ) ; 
 scalar_t__ alloca (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 void* ccv_clamp (unsigned int,int,int) ; 
 int ccv_max (int,float) ; 
 int ccv_min (int,int) ; 

__attribute__((used)) static void _ccv_resample_area_8u(ccv_dense_matrix_t* a, ccv_dense_matrix_t* b)
{
	assert(a->cols > 0 && b->cols > 0);
	ccv_int_alpha* xofs = (ccv_int_alpha*)alloca(sizeof(ccv_int_alpha) * a->cols * 2);
	int ch = ccv_clamp(CCV_GET_CHANNEL(a->type), 1, 4);
	double scale_x = (double)a->cols / b->cols;
	double scale_y = (double)a->rows / b->rows;
	// double scale = 1.f / (scale_x * scale_y);
	unsigned int inv_scale_256 = (int)(scale_x * scale_y * 0x10000);
	int dx, dy, sx, sy, i, k;
	for (dx = 0, k = 0; dx < b->cols; dx++)
	{
		double fsx1 = dx * scale_x, fsx2 = fsx1 + scale_x;
		int sx1 = (int)(fsx1 + 1.0 - 1e-6), sx2 = (int)(fsx2);
		sx1 = ccv_min(sx1, a->cols - 1);
		sx2 = ccv_min(sx2, a->cols - 1);

		if (sx1 > fsx1)
		{
			xofs[k].di = dx * ch;
			xofs[k].si = (sx1 - 1) * ch;
			xofs[k++].alpha = (unsigned int)((sx1 - fsx1) * 0x100);
		}

		for (sx = sx1; sx < sx2; sx++)
		{
			xofs[k].di = dx * ch;
			xofs[k].si = sx * ch;
			xofs[k++].alpha = 256;
		}

		if (fsx2 - sx2 > 1e-3)
		{
			xofs[k].di = dx * ch;
			xofs[k].si = sx2 * ch;
			xofs[k++].alpha = (unsigned int)((fsx2 - sx2) * 256);
		}
	}
	int xofs_count = k;
	unsigned int* buf = (unsigned int*)alloca(b->cols * ch * sizeof(unsigned int));
	unsigned int* sum = (unsigned int*)alloca(b->cols * ch * sizeof(unsigned int));
	for (dx = 0; dx < b->cols * ch; dx++)
		buf[dx] = sum[dx] = 0;
	dy = 0;
	for (sy = 0; sy < a->rows; sy++)
	{
		unsigned char* a_ptr = a->data.u8 + a->step * sy;
		for (k = 0; k < xofs_count; k++)
		{
			int dxn = xofs[k].di;
			unsigned int alpha = xofs[k].alpha;
			for (i = 0; i < ch; i++)
				buf[dxn + i] += a_ptr[xofs[k].si + i] * alpha;
		}
		if ((dy + 1) * scale_y <= sy + 1 || sy == a->rows - 1)
		{
			unsigned int beta = (int)(ccv_max(sy + 1 - (dy + 1) * scale_y, 0.f) * 256);
			unsigned int beta1 = 256 - beta;
			unsigned char* b_ptr = b->data.u8 + b->step * dy;
			if (beta <= 0)
			{
				for (dx = 0; dx < b->cols * ch; dx++)
				{
					b_ptr[dx] = ccv_clamp((sum[dx] + buf[dx] * 256) / inv_scale_256, 0, 255);
					sum[dx] = buf[dx] = 0;
				}
			} else {
				for (dx = 0; dx < b->cols * ch; dx++)
				{
					b_ptr[dx] = ccv_clamp((sum[dx] + buf[dx] * beta1) / inv_scale_256, 0, 255);
					sum[dx] = buf[dx] * beta;
					buf[dx] = 0;
				}
			}
			dy++;
		}
		else
		{
			for(dx = 0; dx < b->cols * ch; dx++)
			{
				sum[dx] += buf[dx] * 256;
				buf[dx] = 0;
			}
		}
	}
}