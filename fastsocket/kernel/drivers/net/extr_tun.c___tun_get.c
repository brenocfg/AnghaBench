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
struct tun_struct {int dummy; } ;
struct tun_file {struct tun_struct* tun; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 scalar_t__ atomic_inc_not_zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct tun_struct *__tun_get(struct tun_file *tfile)
{
	struct tun_struct *tun = NULL;

	if (atomic_inc_not_zero(&tfile->count))
		tun = tfile->tun;

	return tun;
}