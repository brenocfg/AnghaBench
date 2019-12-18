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
typedef  int /*<<< orphan*/  u32 ;
struct se_session {struct ft_sess* fabric_sess_ptr; } ;
struct ft_sess {int /*<<< orphan*/  port_id; } ;

/* Variables and functions */

u32 ft_sess_get_index(struct se_session *se_sess)
{
	struct ft_sess *sess = se_sess->fabric_sess_ptr;

	return sess->port_id;	/* XXX TBD probably not what is needed */
}