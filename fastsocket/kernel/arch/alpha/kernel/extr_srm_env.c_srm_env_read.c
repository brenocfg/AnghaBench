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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ srm_env_t ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int EFAULT ; 
 unsigned long callback_getenv (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
srm_env_read(char *page, char **start, off_t off, int count, int *eof,
		void *data)
{
	int		nbytes;
	unsigned long	ret;
	srm_env_t	*entry;

	if (off != 0) {
		*eof = 1;
		return 0;
	}

	entry	= (srm_env_t *) data;
	ret	= callback_getenv(entry->id, page, count);

	if ((ret >> 61) == 0) {
		nbytes = (int) ret;
		*eof = 1;
	} else
		nbytes = -EFAULT;

	return nbytes;
}