#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int step; } ;
typedef  TYPE_1__ ccv_dense_matrix_t ;

/* Variables and functions */
 int CCV_8U ; 
 int CCV_C1 ; 
 int CCV_C3 ; 
 int CCV_C4 ; 
#define  CCV_IO_ABGR_RAW 134 
#define  CCV_IO_ARGB_RAW 133 
#define  CCV_IO_BGRA_RAW 132 
#define  CCV_IO_BGR_RAW 131 
 int CCV_IO_FINAL ; 
#define  CCV_IO_GRAY_RAW 130 
 int CCV_IO_NO_COPY ; 
#define  CCV_IO_RGBA_RAW 129 
#define  CCV_IO_RGB_RAW 128 
 int CCV_NO_DATA_ALLOC ; 
 int /*<<< orphan*/  _ccv_read_abgr_raw (TYPE_1__**,void*,int,int,int,int) ; 
 int /*<<< orphan*/  _ccv_read_argb_raw (TYPE_1__**,void*,int,int,int,int) ; 
 int /*<<< orphan*/  _ccv_read_bgr_raw (TYPE_1__**,void*,int,int,int,int) ; 
 int /*<<< orphan*/  _ccv_read_bgra_raw (TYPE_1__**,void*,int,int,int,int) ; 
 int /*<<< orphan*/  _ccv_read_gray_raw (TYPE_1__**,void*,int,int,int,int) ; 
 int /*<<< orphan*/  _ccv_read_rgb_raw (TYPE_1__**,void*,int,int,int,int) ; 
 int /*<<< orphan*/  _ccv_read_rgba_raw (TYPE_1__**,void*,int,int,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* ccv_dense_matrix_new (int,int,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_make_matrix_immutable (TYPE_1__*) ; 

__attribute__((used)) static int _ccv_read_raw(ccv_dense_matrix_t** x, void* data, int type, int rows, int cols, int scanline)
{
	assert(rows > 0 && cols > 0 && scanline > 0);
	if (type & CCV_IO_NO_COPY)
	{
		// there is no conversion that we can apply if it is NO_COPY mode
		// NO_COPY mode generate an "unreusable" matrix, which requires you to
		// manually release its data block (which is, in fact the same data
		// block you passed in)
		int ctype = CCV_8U | CCV_C1;
		switch (type & 0xFF)
		{
			case CCV_IO_RGB_RAW:
			case CCV_IO_BGR_RAW:
				ctype = CCV_8U | CCV_C3;
				break;
			case CCV_IO_RGBA_RAW:
			case CCV_IO_ARGB_RAW:
			case CCV_IO_BGRA_RAW:
			case CCV_IO_ABGR_RAW:
				ctype = CCV_8U | CCV_C4;
				break;
			case CCV_IO_GRAY_RAW:
			default:
				/* default one */
				break;
		}
		*x = ccv_dense_matrix_new(rows, cols, ctype | CCV_NO_DATA_ALLOC, data, 0);
		(*x)->step = scanline;
	} else {
		switch (type & 0xFF)
		{
			case CCV_IO_RGB_RAW:
				_ccv_read_rgb_raw(x, data, type, rows, cols, scanline);
				break;
			case CCV_IO_RGBA_RAW:
				_ccv_read_rgba_raw(x, data, type, rows, cols, scanline);
				break;
			case CCV_IO_ARGB_RAW:
				_ccv_read_argb_raw(x, data, type, rows, cols, scanline);
				break;
			case CCV_IO_BGR_RAW:
				_ccv_read_bgr_raw(x, data, type, rows, cols, scanline);
				break;
			case CCV_IO_BGRA_RAW:
				_ccv_read_bgra_raw(x, data, type, rows, cols, scanline);
				break;
			case CCV_IO_ABGR_RAW:
				_ccv_read_abgr_raw(x, data, type, rows, cols, scanline);
				break;
			case CCV_IO_GRAY_RAW:
				_ccv_read_gray_raw(x, data, type, rows, cols, scanline);
				break;
		}
	}
	if (*x != 0)
		ccv_make_matrix_immutable(*x);
	return CCV_IO_FINAL;
}