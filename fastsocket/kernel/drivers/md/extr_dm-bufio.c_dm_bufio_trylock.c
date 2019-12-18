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
struct dm_bufio_client {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int mutex_trylock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dm_bufio_trylock(struct dm_bufio_client *c)
{
	return mutex_trylock(&c->lock);
}