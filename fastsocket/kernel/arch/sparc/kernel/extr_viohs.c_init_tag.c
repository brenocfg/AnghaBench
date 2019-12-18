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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct vio_msg_tag {int /*<<< orphan*/  stype_env; void* stype; void* type; } ;

/* Variables and functions */

__attribute__((used)) static void init_tag(struct vio_msg_tag *tag, u8 type, u8 stype, u16 stype_env)
{
	tag->type = type;
	tag->stype = stype;
	tag->stype_env = stype_env;
}