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
typedef  int u8 ;
struct bcm3510_state {int /*<<< orphan*/  hab_mutex; } ;

/* Variables and functions */
 int EAGAIN ; 
 int bcm3510_hab_get_response (struct bcm3510_state*,int*,int) ; 
 int bcm3510_hab_send_request (struct bcm3510_state*,int*,int) ; 
 int /*<<< orphan*/  dbufout (int*,int,int /*<<< orphan*/  (*) (char*)) ; 
 int /*<<< orphan*/  deb_hab (char*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm3510_do_hab_cmd(struct bcm3510_state *st, u8 cmd, u8 msgid, u8 *obuf, u8 olen, u8 *ibuf, u8 ilen)
{
	u8 ob[olen+2],ib[ilen+2];
	int ret = 0;

	ob[0] = cmd;
	ob[1] = msgid;
	memcpy(&ob[2],obuf,olen);

	deb_hab("hab snd: ");
	dbufout(ob,olen+2,deb_hab);
	deb_hab("\n");

	if (mutex_lock_interruptible(&st->hab_mutex) < 0)
		return -EAGAIN;

	if ((ret = bcm3510_hab_send_request(st, ob, olen+2)) < 0 ||
		(ret = bcm3510_hab_get_response(st, ib, ilen+2)) < 0)
		goto error;

	deb_hab("hab get: ");
	dbufout(ib,ilen+2,deb_hab);
	deb_hab("\n");

	memcpy(ibuf,&ib[2],ilen);
error:
	mutex_unlock(&st->hab_mutex);
	return ret;
}