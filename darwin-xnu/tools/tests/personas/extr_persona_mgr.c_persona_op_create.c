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
typedef  int /*<<< orphan*/  uid_t ;
struct kpersona_info {int /*<<< orphan*/  persona_info_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERSONA_INFO_V1 ; 
 int /*<<< orphan*/  dump_kpersona (int /*<<< orphan*/ *,struct kpersona_info*) ; 
 int /*<<< orphan*/  err (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  info (char*,...) ; 
 int kpersona_alloc (struct kpersona_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int persona_op_create(struct kpersona_info *ki)
{
	int ret;
	uid_t persona_id = 0;

	info("Creating persona...");
	ki->persona_info_version = PERSONA_INFO_V1;
	ret = kpersona_alloc(ki, &persona_id);
	if (ret == 0) {
		info("Created persona %d:", persona_id);
		dump_kpersona(NULL, ki);
	} else {
		err("kpersona_alloc return %d (errno:%d)", ret, errno);
	}

	return ret;
}