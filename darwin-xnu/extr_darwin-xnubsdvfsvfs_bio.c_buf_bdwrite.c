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
 int /*<<< orphan*/  bdwrite_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

errno_t
buf_bdwrite(buf_t bp)
{
	return (bdwrite_internal(bp, 0));
}