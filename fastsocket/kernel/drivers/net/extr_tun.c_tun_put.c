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
struct tun_struct {struct tun_file* tfile; } ;
struct tun_file {int /*<<< orphan*/  tun; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tun_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tun_put(struct tun_struct *tun)
{
	struct tun_file *tfile = tun->tfile;

	if (atomic_dec_and_test(&tfile->count))
		tun_detach(tfile->tun);
}