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
struct _reent {int /*<<< orphan*/  _errno; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTSUP ; 

__attribute__((used)) static int sd_fat_link_r (struct _reent *r, const char *existing, const char *newLink)
{
    r->_errno = ENOTSUP;
    return -1;
}