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
struct bfa_reqq_wait_s {void (* qresume ) (void*) ;void* cbarg; } ;

/* Variables and functions */

__attribute__((used)) static inline void
bfa_reqq_winit(struct bfa_reqq_wait_s *wqe, void (*qresume) (void *cbarg),
	       void *cbarg)
{
	wqe->qresume = qresume;
	wqe->cbarg = cbarg;
}