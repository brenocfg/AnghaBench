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
struct kqworkq {int dummy; } ;
struct kqworkloop {int dummy; } ;
struct kqfile {int dummy; } ;
struct knote {int dummy; } ;

/* Variables and functions */
 void* knote_zone ; 
 int /*<<< orphan*/  kq_lck_attr ; 
 int /*<<< orphan*/  kq_lck_grp ; 
 int /*<<< orphan*/  kq_lck_grp_attr ; 
 void* kqfile_zone ; 
 void* kqworkloop_zone ; 
 void* kqworkq_zone ; 
 int /*<<< orphan*/  lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  memorystatus_kevent_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* zinit (int,int,int,char*) ; 

void
knote_init(void)
{
	knote_zone = zinit(sizeof(struct knote), 8192*sizeof(struct knote),
	                   8192, "knote zone");

	kqfile_zone = zinit(sizeof(struct kqfile), 8192*sizeof(struct kqfile),
	                    8192, "kqueue file zone");

	kqworkq_zone = zinit(sizeof(struct kqworkq), 8192*sizeof(struct kqworkq),
	                    8192, "kqueue workq zone");

	kqworkloop_zone = zinit(sizeof(struct kqworkloop), 8192*sizeof(struct kqworkloop),
	                    8192, "kqueue workloop zone");

	/* allocate kq lock group attribute and group */
	kq_lck_grp_attr = lck_grp_attr_alloc_init();

	kq_lck_grp = lck_grp_alloc_init("kqueue",  kq_lck_grp_attr);

	/* Allocate kq lock attribute */
	kq_lck_attr = lck_attr_alloc_init();

#if CONFIG_MEMORYSTATUS
	/* Initialize the memorystatus list lock */
	memorystatus_kevent_init(kq_lck_grp, kq_lck_attr);
#endif
}