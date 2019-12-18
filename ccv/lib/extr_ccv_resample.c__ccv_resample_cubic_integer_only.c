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
struct TYPE_5__ {unsigned char* u8; } ;
struct TYPE_6__ {int type; int cols; float rows; TYPE_1__ data; } ;
typedef  TYPE_2__ ccv_dense_matrix_t ;
typedef  int /*<<< orphan*/  ccv_cubic_integer_coeffs_t ;

/* Variables and functions */
 scalar_t__ CCV_32S ; 
 scalar_t__ CCV_64S ; 
 int CCV_8U ; 
 int CCV_GET_CHANNEL (int) ; 
 scalar_t__ CCV_GET_DATA_TYPE (int) ; 
 int CCV_GET_DATA_TYPE_SIZE (int) ; 
 int /*<<< orphan*/  _ccv_init_cubic_integer_coeffs (int,int,float,int /*<<< orphan*/ *) ; 
 scalar_t__ alloca (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ccv_matrix_getter (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_matrix_setter_getter_integer_only ; 
 int /*<<< orphan*/  ccv_matrix_setter_integer_only ; 
 int /*<<< orphan*/  for_block ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _ccv_resample_cubic_integer_only(ccv_dense_matrix_t* a, ccv_dense_matrix_t* b)
{
	assert(CCV_GET_DATA_TYPE(b->type) == CCV_8U || CCV_GET_DATA_TYPE(b->type) == CCV_32S || CCV_GET_DATA_TYPE(b->type) == CCV_64S);
	int i, j, k, ch = CCV_GET_CHANNEL(a->type);
	int no_8u_type = (b->type & CCV_8U) ? CCV_32S : b->type;
	assert(b->cols > 0);
	ccv_cubic_integer_coeffs_t* xofs = (ccv_cubic_integer_coeffs_t*)alloca(sizeof(ccv_cubic_integer_coeffs_t) * b->cols);
	float scale_x = (float)a->cols / b->cols;
	for (i = 0; i < b->cols; i++)
	{
		float sx = (i + 0.5) * scale_x - 0.5;
		_ccv_init_cubic_integer_coeffs((int)sx, a->cols, sx, xofs + i);
	}
	float scale_y = (float)a->rows / b->rows;
	int bufstep = b->cols * ch * CCV_GET_DATA_TYPE_SIZE(no_8u_type);
	unsigned char* buf = (unsigned char*)alloca(bufstep * 4);
#ifdef __clang_analyzer__
	memset(buf, 0, bufstep * 4);
#endif
	unsigned char* a_ptr = a->data.u8;
	unsigned char* b_ptr = b->data.u8;
	int psi = -1, siy = 0;
#define for_block(_for_get_a, _for_set, _for_get, _for_set_b) \
	for (i = 0; i < b->rows; i++) \
	{ \
		ccv_cubic_integer_coeffs_t yofs; \
		float sy = (i + 0.5) * scale_y - 0.5; \
		_ccv_init_cubic_integer_coeffs((int)sy, a->rows, sy, &yofs); \
		if (yofs.si[3] > psi) \
		{ \
			for (; siy <= yofs.si[3]; siy++) \
			{ \
				unsigned char* row = buf + (siy & 0x3) * bufstep; \
				for (j = 0; j < b->cols; j++) \
					for (k = 0; k < ch; k++) \
						_for_set(row, j * ch + k, _for_get_a(a_ptr, xofs[j].si[0] * ch + k, 0) * xofs[j].coeffs[0] + \
												  _for_get_a(a_ptr, xofs[j].si[1] * ch + k, 0) * xofs[j].coeffs[1] + \
												  _for_get_a(a_ptr, xofs[j].si[2] * ch + k, 0) * xofs[j].coeffs[2] + \
												  _for_get_a(a_ptr, xofs[j].si[3] * ch + k, 0) * xofs[j].coeffs[3], 0); \
				a_ptr += a->step; \
			} \
			psi = yofs.si[3]; \
		} \
		unsigned char* row[4] = { \
			buf + (yofs.si[0] & 0x3) * bufstep, \
			buf + (yofs.si[1] & 0x3) * bufstep, \
			buf + (yofs.si[2] & 0x3) * bufstep, \
			buf + (yofs.si[3] & 0x3) * bufstep, \
		}; \
		for (j = 0; j < b->cols * ch; j++) \
			_for_set_b(b_ptr, j, ccv_descale(_for_get(row[0], j, 0) * yofs.coeffs[0] + _for_get(row[1], j, 0) * yofs.coeffs[1] + \
											 _for_get(row[2], j, 0) * yofs.coeffs[2] + _for_get(row[3], j, 0) * yofs.coeffs[3], 12), 0); \
		b_ptr += b->step; \
	}
	ccv_matrix_getter(a->type, ccv_matrix_setter_getter_integer_only, no_8u_type, ccv_matrix_setter_integer_only, b->type, for_block);
#undef for_block
}