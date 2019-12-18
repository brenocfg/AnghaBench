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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/ * mbuf_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  mbuf_adj (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

errno_t
gss_strip_mbuf(mbuf_t chain, ssize_t size)
{
	if (chain == NULL)
		return (EINVAL);

	mbuf_adj(chain, size);

	return (0);
}