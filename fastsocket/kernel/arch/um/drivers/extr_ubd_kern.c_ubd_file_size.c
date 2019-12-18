#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* file; } ;
struct ubd {char* file; TYPE_1__ cow; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int os_file_size (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ubd_file_size(struct ubd *ubd_dev, __u64 *size_out)
{
	char *file;

	file = ubd_dev->cow.file ? ubd_dev->cow.file : ubd_dev->file;
	return os_file_size(file, size_out);
}