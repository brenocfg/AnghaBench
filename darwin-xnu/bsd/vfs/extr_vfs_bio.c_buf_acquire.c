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
typedef  int /*<<< orphan*/  errno_t ;
typedef  int /*<<< orphan*/  buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  buf_acquire_locked (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  buf_mtxp ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 

errno_t
buf_acquire(buf_t bp, int flags, int slpflag, int slptimeo) {
        errno_t error;

        lck_mtx_lock_spin(buf_mtxp);

	error = buf_acquire_locked(bp, flags, slpflag, slptimeo);

       	lck_mtx_unlock(buf_mtxp);

	return (error);
}