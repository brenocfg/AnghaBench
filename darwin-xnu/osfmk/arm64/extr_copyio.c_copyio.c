#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int copyio_type_t ;

/* Variables and functions */
#define  COPYIO_IN 131 
#define  COPYIO_INSTR 130 
#define  COPYIO_IN_WORD 129 
#define  COPYIO_OUT 128 
 int EFAULT ; 
 int EINVAL ; 
 uintptr_t TBI_MASK ; 
 int /*<<< orphan*/  __asan_loadN (uintptr_t,scalar_t__) ; 
 int /*<<< orphan*/  __asan_storeN (uintptr_t,scalar_t__) ; 
 scalar_t__ __improbable (int) ; 
 scalar_t__ __probable (int /*<<< orphan*/ ) ; 
 int _bcopyin (char const*,char*,scalar_t__) ; 
 int _bcopyinstr (char const*,char*,scalar_t__,scalar_t__*) ; 
 int _bcopyout (char const*,char*,scalar_t__) ; 
 int _copyin_word (char const*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  copyio_zalloc_check ; 
 int /*<<< orphan*/  panic (char*,void*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  user_access_disable () ; 
 int /*<<< orphan*/  user_access_enable () ; 
 scalar_t__ zone_element_size (void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
copyio(copyio_type_t copytype, const char *src, char *dst,
	   vm_size_t nbytes, vm_size_t *lencopied)
{
	int result = 0;
	vm_size_t bytes_copied = 0;
	vm_size_t kernel_buf_size = 0;
	void * kernel_addr = NULL;

	/* Reject TBI addresses */
	if (copytype == COPYIO_OUT) {
		if ((uintptr_t)dst & TBI_MASK)
			return EINVAL;
	} else {
		if ((uintptr_t)src & TBI_MASK)
			return EINVAL;
	}

	if (__probable(copyio_zalloc_check)) {
		if (copytype == COPYIO_IN || copytype == COPYIO_INSTR || copytype == COPYIO_IN_WORD) {
			kernel_addr = (void*)dst;
		} else if (copytype == COPYIO_OUT) {
			kernel_addr = (void*)(uintptr_t)src;
		}
		if (kernel_addr)
			kernel_buf_size = zone_element_size(kernel_addr, NULL);
		if (__improbable(kernel_buf_size && kernel_buf_size < nbytes))
			panic("copyio: kernel buffer %p has size %lu < nbytes %lu", kernel_addr, kernel_buf_size, nbytes);
	}

#if KASAN
	/* For user copies, asan-check the kernel-side buffer */
	if (copytype == COPYIO_IN || copytype == COPYIO_INSTR || copytype == COPYIO_IN_WORD) {
		__asan_storeN((uintptr_t)dst, nbytes);
	} else if (copytype == COPYIO_OUT) {
		__asan_loadN((uintptr_t)src, nbytes);
	}
#endif

	user_access_enable();

	/* Select copy routines based on direction:
	 *   COPYIO_IN - Use unprivileged loads to read from user address
	 *   COPYIO_OUT - Use unprivleged stores to write to user address
	 */

	switch (copytype) {
	case COPYIO_IN:
		result = _bcopyin(src, dst, nbytes);
		break;
	case COPYIO_INSTR:
		result = _bcopyinstr(src, dst, nbytes, &bytes_copied);
		if (result != EFAULT) {
			*lencopied = bytes_copied;
		}
		break;
	case COPYIO_IN_WORD:
		result = _copyin_word(src, (uint64_t *)(uintptr_t)dst, nbytes);
		break;
	case COPYIO_OUT:
		result = _bcopyout(src, dst, nbytes);
		break;
	default:
		result = EINVAL;
	}

	user_access_disable();
	return result;
}