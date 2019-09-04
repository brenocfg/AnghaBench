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
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int ERANGE ; 
 int MAX_UPTRS ; 
 int /*<<< orphan*/  USER_ADDR_NULL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (void*,int) ; 
 int copyout (void*,int /*<<< orphan*/ ,size_t) ; 
 void* kalloc (int) ; 
 int /*<<< orphan*/  kevent_proc_copy_uptrs (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  kfree (void*,int) ; 
 scalar_t__ os_mul_overflow (int /*<<< orphan*/ ,int,size_t*) ; 

int
proc_pidlistuptrs(proc_t p, user_addr_t buffer, uint32_t buffersize, int32_t *retval)
{
	uint32_t count = 0;
	int error = 0;
	void *kbuf = NULL;
	int32_t nuptrs = 0;

	if (buffer != USER_ADDR_NULL) {
		count = buffersize / sizeof(uint64_t);
		if (count > MAX_UPTRS) {
			count = MAX_UPTRS;
		}
		if (count > 0) {
			buffersize = count * sizeof(uint64_t);
			kbuf = kalloc(buffersize);
			bzero(kbuf, buffersize);
			assert(kbuf != NULL);
		} else {
			buffersize = 0;
		}
	} else {
		buffersize = 0;
	}

	nuptrs = kevent_proc_copy_uptrs(p, kbuf, buffersize);

	if (kbuf) {
		size_t copysize;
		if (os_mul_overflow(nuptrs, sizeof(uint64_t), &copysize)) {
			error = ERANGE;
			goto out;
		}
		if (copysize > buffersize) {
			copysize = buffersize;
		}
		error = copyout(kbuf, buffer, copysize);
	}

out:
	*retval = nuptrs;

	if (kbuf) {
		kfree(kbuf, buffersize);
		kbuf = NULL;
	}

	return error;
}