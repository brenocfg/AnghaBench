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
struct hidp_session {int dummy; } ;

/* Variables and functions */
 int __hidp_send_ctrl_message (struct hidp_session*,unsigned char,unsigned char*,int) ; 
 int /*<<< orphan*/  hidp_schedule (struct hidp_session*) ; 

__attribute__((used)) static inline int hidp_send_ctrl_message(struct hidp_session *session,
			unsigned char hdr, unsigned char *data, int size)
{
	int err;

	err = __hidp_send_ctrl_message(session, hdr, data, size);

	hidp_schedule(session);

	return err;
}