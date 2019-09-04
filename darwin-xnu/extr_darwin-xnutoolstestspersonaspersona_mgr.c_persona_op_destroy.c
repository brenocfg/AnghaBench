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
struct kpersona_info {int /*<<< orphan*/  persona_id; int /*<<< orphan*/  persona_info_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERSONA_INFO_V1 ; 
 int /*<<< orphan*/  err_print (char*) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 
 int kpersona_dealloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int persona_op_destroy(struct kpersona_info *ki)
{
	int ret;

	info("Destroying Persona %d...", ki->persona_id);
	ki->persona_info_version = PERSONA_INFO_V1;
	ret = kpersona_dealloc(ki->persona_id);
	if (ret < 0)
		err_print("destroy failed!");

	return ret;
}