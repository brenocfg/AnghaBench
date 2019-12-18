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
typedef  int u16 ;
struct asd_ha_struct {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int asd_ddbsite_read_word (struct asd_ha_struct*,int,int) ; 
 int asd_ddbsite_update_word (struct asd_ha_struct*,int,int,int,int) ; 

__attribute__((used)) static inline int asd_ddbsite_update_byte(struct asd_ha_struct *asd_ha,
					  u16 ddb_site_no, u16 offs,
					  u8 _oldval, u8 _newval)
{
	u16 base = offs & ~1;
	u16 oval;
	u16 nval = asd_ddbsite_read_word(asd_ha, ddb_site_no, base);
	if (offs & 1) {
		if ((nval >> 8) != _oldval)
			return -EAGAIN;
		nval = (_newval << 8) | (nval & 0xFF);
		oval = (_oldval << 8) | (nval & 0xFF);
	} else {
		if ((nval & 0xFF) != _oldval)
			return -EAGAIN;
		nval = (nval & 0xFF00) | _newval;
		oval = (nval & 0xFF00) | _oldval;
	}
	return asd_ddbsite_update_word(asd_ha, ddb_site_no, base, oval, nval);
}