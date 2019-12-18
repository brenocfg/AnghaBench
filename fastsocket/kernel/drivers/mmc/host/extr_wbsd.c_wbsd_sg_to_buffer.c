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
struct wbsd_host {int /*<<< orphan*/  cur_sg; } ;

/* Variables and functions */
 char* sg_virt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline char *wbsd_sg_to_buffer(struct wbsd_host *host)
{
	return sg_virt(host->cur_sg);
}