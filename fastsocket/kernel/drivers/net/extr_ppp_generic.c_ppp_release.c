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
struct ppp_file {int kind; int /*<<< orphan*/  refcnt; } ;
struct ppp {struct file* owner; } ;
struct inode {int dummy; } ;
struct file {struct ppp_file* private_data; } ;

/* Variables and functions */
#define  CHANNEL 129 
#define  INTERFACE 128 
 int /*<<< orphan*/  PF_TO_CHANNEL (struct ppp_file*) ; 
 struct ppp* PF_TO_PPP (struct ppp_file*) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppp_destroy_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppp_destroy_interface (struct ppp*) ; 
 int /*<<< orphan*/  ppp_shutdown_interface (struct ppp*) ; 

__attribute__((used)) static int ppp_release(struct inode *unused, struct file *file)
{
	struct ppp_file *pf = file->private_data;
	struct ppp *ppp;

	if (pf) {
		file->private_data = NULL;
		if (pf->kind == INTERFACE) {
			ppp = PF_TO_PPP(pf);
			if (file == ppp->owner)
				ppp_shutdown_interface(ppp);
		}
		if (atomic_dec_and_test(&pf->refcnt)) {
			switch (pf->kind) {
			case INTERFACE:
				ppp_destroy_interface(PF_TO_PPP(pf));
				break;
			case CHANNEL:
				ppp_destroy_channel(PF_TO_CHANNEL(pf));
				break;
			}
		}
	}
	return 0;
}