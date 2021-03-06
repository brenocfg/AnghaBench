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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IFCHR ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int uart_fstat(int fd, struct stat * st)
{
    assert(fd >=0 && fd < 3);
    st->st_mode = S_IFCHR;
    return 0;
}