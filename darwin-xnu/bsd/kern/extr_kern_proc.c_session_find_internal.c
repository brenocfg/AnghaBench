#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct session* le_next; } ;
struct session {scalar_t__ s_sid; TYPE_1__ s_hash; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_4__ {struct session* lh_first; } ;

/* Variables and functions */
 TYPE_2__* SESSHASH (scalar_t__) ; 

struct session *
session_find_internal(pid_t sessid)
{
	struct session *sess;

	for (sess = SESSHASH(sessid)->lh_first; sess != 0; sess = sess->s_hash.le_next)
		if (sess->s_sid == sessid)
			return (sess);
	return (NULL);
}