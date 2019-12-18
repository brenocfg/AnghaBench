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
typedef  int /*<<< orphan*/  u16 ;
struct hermes {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int HERMES_DATA0 ; 
 int HERMES_DATA1 ; 
 int hermes_bap_seek (struct hermes*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hermes_write_bytes (struct hermes*,int,void const*,int) ; 

__attribute__((used)) static int hermes_bap_pwrite(struct hermes *hw, int bap, const void *buf,
			     int len, u16 id, u16 offset)
{
	int dreg = bap ? HERMES_DATA1 : HERMES_DATA0;
	int err = 0;

	if (len < 0)
		return -EINVAL;

	err = hermes_bap_seek(hw, bap, id, offset);
	if (err)
		goto out;

	/* Actually do the transfer */
	hermes_write_bytes(hw, dreg, buf, len);

 out:
	return err;
}