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
struct workqueue {int dummy; } ;

/* Variables and functions */
 int WQ_EXITING ; 
 int _wq_flags (struct workqueue*) ; 

__attribute__((used)) static inline bool
_wq_exiting(struct workqueue *wq)
{
	return _wq_flags(wq) & WQ_EXITING;
}