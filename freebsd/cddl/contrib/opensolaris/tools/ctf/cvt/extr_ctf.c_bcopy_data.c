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
typedef  size_t ssize_t ;
typedef  size_t caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (void*,size_t,size_t) ; 

__attribute__((used)) static ssize_t
bcopy_data(void *buf, size_t n, void *data)
{
	caddr_t *posp = (caddr_t *)data;
	bcopy(buf, *posp, n);
	*posp += n;
	return (n);
}