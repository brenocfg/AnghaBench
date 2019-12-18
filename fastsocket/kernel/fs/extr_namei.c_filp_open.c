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
struct filename {char const* name; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 struct file* do_filp_open (int /*<<< orphan*/ ,struct filename*,int,int,int /*<<< orphan*/ ) ; 

struct file *filp_open(const char *filename, int flags, int mode)
{
	struct filename name = { .name = filename };

	return do_filp_open(AT_FDCWD, &name, flags, mode, 0);
}