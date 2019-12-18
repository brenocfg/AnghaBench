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
struct splice_pipe_desc {int /*<<< orphan*/ * pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  page_cache_release (int /*<<< orphan*/ ) ; 

void spd_release_page(struct splice_pipe_desc *spd, unsigned int i)
{
	page_cache_release(spd->pages[i]);
}