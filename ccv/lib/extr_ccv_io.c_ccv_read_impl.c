#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; char* buffer; int /*<<< orphan*/  pos; } ;
typedef  TYPE_1__ ccv_io_mem_t ;
typedef  int /*<<< orphan*/  ccv_dense_matrix_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CCV_IO_ANY_FILE ; 
 int CCV_IO_ANY_RAW ; 
 int CCV_IO_ANY_STREAM ; 
 int CCV_IO_DEFLATE_STREAM ; 
 int CCV_IO_ERROR ; 
 int CCV_IO_UNKNOWN ; 
 int _ccv_read_and_close_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 int _ccv_read_raw (int /*<<< orphan*/ **,void*,int,int,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * fmemopen (void*,size_t,char*) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/ * funopen (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readfn ; 
 int /*<<< orphan*/  seekfn ; 

int ccv_read_impl(const void* in, ccv_dense_matrix_t** x, int type, int rows, int cols, int scanline)
{
	FILE* fd = 0;
	if (type & CCV_IO_ANY_FILE)
	{
		assert(rows == 0 && cols == 0 && scanline == 0);
		fd = fopen((const char*)in, "rb");
		if (!fd)
			return CCV_IO_ERROR;
		return _ccv_read_and_close_fd(fd, x, type);
	} else if (type & CCV_IO_ANY_STREAM) {
		assert(rows > 8 && cols == 0 && scanline == 0);
		assert((type & 0xFF) != CCV_IO_DEFLATE_STREAM); // deflate stream (compressed stream) is not supported yet
#if _XOPEN_SOURCE >= 700 || _POSIX_C_SOURCE >= 200809L || defined(__APPLE__) || defined(BSD)
		// this is only supported by glibc
#if _XOPEN_SOURCE >= 700 || _POSIX_C_SOURCE >= 200809L
		fd = fmemopen((void*)in, (size_t)rows, "rb");
#else
		ccv_io_mem_t mem = {
			.size = rows,
			.pos = 0,
			.buffer = (char*)in,
		};
		fd = funopen(&mem, readfn, 0, seekfn, 0);
#endif
		if (!fd)
			return CCV_IO_ERROR;
		// mimicking itself as a "file"
		type = (type & ~0x10) | 0x20;
		return _ccv_read_and_close_fd(fd, x, type);
#endif
	} else if (type & CCV_IO_ANY_RAW) {
		return _ccv_read_raw(x, (void*)in /* it can be modifiable if it is NO_COPY mode */, type, rows, cols, scanline);
	}
	return CCV_IO_UNKNOWN;
}