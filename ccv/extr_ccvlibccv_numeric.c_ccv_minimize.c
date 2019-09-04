#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {double max_iter; double sig; double rho; double extrap; double interp; double ratio; } ;
typedef  TYPE_2__ ccv_minimize_param_t ;
typedef  scalar_t__ (* ccv_minimize_f ) (TYPE_3__*,double*,TYPE_3__*,void*) ;
struct TYPE_13__ {unsigned char* u8; } ;
struct TYPE_15__ {int rows; int cols; int step; int /*<<< orphan*/  type; TYPE_1__ data; } ;
typedef  TYPE_3__ ccv_dense_matrix_t ;

/* Variables and functions */
 TYPE_3__* ccv_dense_matrix_new (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double ccv_get_value (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  ccv_matrix_free (TYPE_3__*) ; 
 double ccv_max (double,double) ; 
 double ccv_min (double,double) ; 
 int /*<<< orphan*/  ccv_set_value (int /*<<< orphan*/ ,unsigned char*,int,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_zero (TYPE_3__*) ; 
 double fabs (double) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 double sqrt (double) ; 

void ccv_minimize(ccv_dense_matrix_t* x, int length, double red, ccv_minimize_f func, ccv_minimize_param_t params, void* data)
{
	ccv_dense_matrix_t* df0 = ccv_dense_matrix_new(x->rows, x->cols, x->type, 0, 0);
	ccv_zero(df0);
	ccv_dense_matrix_t* df3 = ccv_dense_matrix_new(x->rows, x->cols, x->type, 0, 0);
	ccv_zero(df3);
	ccv_dense_matrix_t* dF0 = ccv_dense_matrix_new(x->rows, x->cols, x->type, 0, 0);
	ccv_zero(dF0);
	ccv_dense_matrix_t* s = ccv_dense_matrix_new(x->rows, x->cols, x->type, 0, 0);
	ccv_zero(s);
	ccv_dense_matrix_t* x0 = ccv_dense_matrix_new(x->rows, x->cols, x->type, 0, 0);
	ccv_zero(x0);
	ccv_dense_matrix_t* xn = ccv_dense_matrix_new(x->rows, x->cols, x->type, 0, 0);
	ccv_zero(xn);
	
	double F0 = 0, f0 = 0, f1 = 0, f2 = 0, f3 = 0, f4 = 0;
	double x1 = 0, x2 = 0, x3 = 0, x4 = 0;
	double d0 = 0, d1 = 0, d2 = 0, d3 = 0, d4 = 0;
	double A = 0, B = 0;
	int ls_failed = 0;

	int i, j, k;
	func(x, &f0, df0, data);
	d0 = 0;
	unsigned char* df0p = df0->data.u8;
	unsigned char* sp = s->data.u8;
	for (i = 0; i < x->rows; i++)
	{
		for (j = 0; j < x->cols; j++)
		{
			double ss = ccv_get_value(x->type, df0p, j);
			ccv_set_value(x->type, sp, j, -ss, 0);
			d0 += -ss * ss;
		}
		df0p += x->step;
		sp += x->step;
	}
	x3 = red / (1.0 - d0);
	int l = (length > 0) ? length : -length;
	int ls = (length > 0) ? 1 : 0;
	int eh = (length > 0) ? 0 : 1;
	for (k = 0; k < l;)
	{
		k += ls;
		memcpy(x0->data.u8, x->data.u8, x->rows * x->step);
		memcpy(dF0->data.u8, df0->data.u8, x->rows * x->step);
		F0 = f0;
		int m = ccv_min(params.max_iter, (length > 0) ? params.max_iter : l - k);
		for (;;)
		{
			x2 = 0;
			f3 = f2 = f0;
			d2 = d0;
			memcpy(df3->data.u8, df0->data.u8, x->rows * x->step);
			while (m > 0)
			{
				m--;
				k += eh;
				unsigned char* sp = s->data.u8;
				unsigned char* xp = x->data.u8;
				unsigned char* xnp = xn->data.u8;
				for (i = 0; i < x->rows; i++)
				{
					for (j = 0; j < x->cols; j++)
						ccv_set_value(x->type, xnp, j, x3 * ccv_get_value(x->type, sp, j) + ccv_get_value(x->type, xp, j), 0);
					sp += x->step;
					xp += x->step;
					xnp += x->step;
				}
				if (func(xn, &f3, df3, data) == 0)
					break;
				else
					x3 = (x2 + x3) * 0.5;
			}
			if (f3 < F0)
			{
				memcpy(x0->data.u8, xn->data.u8, x->rows * x->step);
				memcpy(dF0->data.u8, df3->data.u8, x->rows * x->step);
				F0 = f3;
			}
			d3 = 0;
			unsigned char* df3p = df3->data.u8;
			unsigned char* sp = s->data.u8;
			for (i = 0; i < x->rows; i++)
			{
				for (j = 0; j < x->cols; j++)
					d3 += ccv_get_value(x->type, df3p, j) * ccv_get_value(x->type, sp, j);
				df3p += x->step;
				sp += x->step;
			}
			if ((d3 > params.sig * d0) || (f3 > f0 + x3 * params.rho * d0) || (m <= 0))
				break;
			x1 = x2; f1 = f2; d1 = d2;
			x2 = x3; f2 = f3; d2 = d3;
			A = 6.0 * (f1 - f2) + 3.0 * (d2 + d1) * (x2 - x1);
			B = 3.0 * (f2 - f1) - (2.0 * d1 + d2) * (x2 - x1);
			x3 = B * B - A * d1 * (x2 - x1);
			if (x3 < 0)
				x3 = x2 * params.extrap;
			else {
				x3 = x1 - d1 * (x2 - x1) * (x2 - x1) / (B + sqrt(x3));
				if (x3 < 0)
					x3 = x2 * params.extrap;
				else {
					if (x3 > x2 * params.extrap)
						x3 = x2 * params.extrap;
					else if (x3 < x2 + params.interp * (x2 - x1))
						x3 = x2 + params.interp * (x2 - x1);
				}
			}
		}
		while (((fabs(d3) > -params.sig * d0) || (f3 > f0 + x3 * params.rho * d0)) && (m > 0))
		{
			if ((d3 > 1e-8) || (f3 > f0 + x3 * params.rho * d0))
			{
				x4 = x3; f4 = f3; d4 = d3;
			} else {
				x2 = x3; f2 = f3; d2 = d3;
			}
			if (f4 > f0)
				x3 = x2 - (0.5 * d2 * (x4 - x2) * (x4 - x2)) / (f4 - f2 - d2 * (x4 - x2));
			else {
				A = 6.0 * (f2 - f4) / (x4 - x2) + 3.0 * (d4 + d2);
				B = 3.0 * (f4 - f2) - (2.0 * d2 + d4) * (x4 - x2);
				x3 = B * B - A * d2 * (x4 - x2) * (x4 - x2);
				x3 = (x3 < 0) ? (x2 + x4) * 0.5 : x2 + (sqrt(x3) - B) / A;
			}
			x3 = ccv_max(ccv_min(x3, x4 - params.interp * (x4 - x2)), x2 + params.interp * (x4 - x2));
			sp = s->data.u8;
			unsigned char* xp = x->data.u8;
			unsigned char* xnp = xn->data.u8;
			for (i = 0; i < x->rows; i++)
			{
				for (j = 0; j < x->cols; j++)
					ccv_set_value(x->type, xnp, j, x3 * ccv_get_value(x->type, sp, j) + ccv_get_value(x->type, xp, j), 0);
				sp += x->step;
				xp += x->step;
				xnp += x->step;
			}
			func(xn, &f3, df3, data);
			if (f3 < F0)
			{
				memcpy(x0->data.u8, xn->data.u8, x->rows * x->step);
				memcpy(dF0->data.u8, df3->data.u8, x->rows * x->step);
				F0 = f3;
			}
			m--;
			k += eh;
			d3 = 0;
			sp = s->data.u8;
			unsigned char* df3p = df3->data.u8;
			for (i = 0; i < x->rows; i++)
			{
				for (j = 0; j < x->cols; j++)
					d3 += ccv_get_value(x->type, df3p, j) * ccv_get_value(x->type, sp, j);
				df3p += x->step;
				sp += x->step;
			}
		}
		if ((fabs(d3) < -params.sig * d0) && (f3 < f0 + x3 * params.rho * d0))
		{
			memcpy(x->data.u8, xn->data.u8, x->rows * x->step);
			f0 = f3;
			double df0_df3 = 0;
			double df3_df3 = 0;
			double df0_df0 = 0;
			unsigned char* df0p = df0->data.u8;
			unsigned char* df3p = df3->data.u8;
			for (i = 0; i < x->rows; i++)
			{
				for (j = 0; j < x->cols; j++)
				{
					df0_df0 += ccv_get_value(x->type, df0p, j) * ccv_get_value(x->type, df0p, j);
					df0_df3 += ccv_get_value(x->type, df0p, j) * ccv_get_value(x->type, df3p, j);
					df3_df3 += ccv_get_value(x->type, df3p, j) * ccv_get_value(x->type, df3p, j);
				}
				df0p += x->step;
				df3p += x->step;
			}
			double slr = (df3_df3 - df0_df3) / df0_df0;
			df3p = df3->data.u8;
			unsigned char* sp = s->data.u8;
			for (i = 0; i < x->rows; i++)
			{
				for (j = 0; j < x->cols; j++)
					ccv_set_value(x->type, sp, j, slr * ccv_get_value(x->type, sp, j) - ccv_get_value(x->type, df3p, j), 0);
				df3p += x->step;
				sp += x->step;
			}
			memcpy(df0->data.u8, df3->data.u8, x->rows * x->step);
			d3 = d0;
			d0 = 0;
			df0p = df0->data.u8;
			sp = s->data.u8;
			for (i = 0; i < x->rows; i++)
			{
				for (j = 0; j < x->cols; j++)
				{
					d0 += ccv_get_value(x->type, df0p, j) * ccv_get_value(x->type, sp, j);
				}
				df0p += x->step;
				sp += x->step;
			}
			if (d0 > 0)
			{
				d0 = 0;
				df0p = df0->data.u8;
				sp = s->data.u8;
				for (i = 0; i < x->rows; i++)
				{
					for (j = 0; j < x->cols; j++)
					{
						double ss = ccv_get_value(x->type, df0p, j);
						ccv_set_value(x->type, sp, j, -ss, 0);
						d0 += -ss * ss;
					}
					df0p += x->step;
					sp += x->step;
				}
			}
			x3 = x3 * ccv_min(params.ratio, d3 / (d0 - 1e-8));
			ls_failed = 0;
		} else {
			memcpy(x->data.u8, x0->data.u8, x->rows * x->step);
			memcpy(df0->data.u8, dF0->data.u8, x->rows * x->step);
			f0 = F0;
			if (ls_failed)
				break;
			d0 = 0;
			unsigned char* df0p = df0->data.u8;
			unsigned char* sp = s->data.u8;
			for (i = 0; i < x->rows; i++)
			{
				for (j = 0; j < x->cols; j++)
				{
					double ss = ccv_get_value(x->type, df0p, j);
					ccv_set_value(x->type, sp, j, -ss, 0);
					d0 += -ss * ss;
				}
				df0p += x->step;
				sp += x->step;
			}
			x3 = red / (1.0 - d0);
			ls_failed = 1;
		}
	}
	ccv_matrix_free(s);
	ccv_matrix_free(x0);
	ccv_matrix_free(xn);
	ccv_matrix_free(dF0);
	ccv_matrix_free(df0);
	ccv_matrix_free(df3);
}