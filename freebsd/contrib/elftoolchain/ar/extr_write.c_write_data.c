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
struct bsdar {int dummy; } ;
struct archive {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  archive_error_string (struct archive*) ; 
 scalar_t__ archive_write_data (struct archive*,void const*,size_t) ; 
 int /*<<< orphan*/  bsdar_errc (struct bsdar*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
write_data(struct bsdar *bsdar, struct archive *a, const void *buf, size_t s)
{
	if (archive_write_data(a, buf, s) != (ssize_t)s)
		bsdar_errc(bsdar, 0, "%s", archive_error_string(a));
}