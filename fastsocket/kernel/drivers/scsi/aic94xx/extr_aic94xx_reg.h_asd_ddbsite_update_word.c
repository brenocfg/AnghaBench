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
typedef  scalar_t__ u16 ;
struct asd_ha_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANEWDATA ; 
 int /*<<< orphan*/  AOLDDATA ; 
 int ATOMICDONE ; 
 int ATOMICERR ; 
 int /*<<< orphan*/  ATOMICSTATCTL ; 
 int ATOMICWIN ; 
 int EAGAIN ; 
 int EFAULT ; 
 scalar_t__ asd_ddbsite_read_word (struct asd_ha_struct*,scalar_t__,scalar_t__) ; 
 int asd_read_reg_byte (struct asd_ha_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asd_write_reg_word (struct asd_ha_struct*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline int asd_ddbsite_update_word(struct asd_ha_struct *asd_ha,
					  u16 ddb_site_no, u16 offs,
					  u16 oldval, u16 newval)
{
	u8  done;
	u16 oval = asd_ddbsite_read_word(asd_ha, ddb_site_no, offs);
	if (oval != oldval)
		return -EAGAIN;
	asd_write_reg_word(asd_ha, AOLDDATA, oldval);
	asd_write_reg_word(asd_ha, ANEWDATA, newval);
	do {
		done = asd_read_reg_byte(asd_ha, ATOMICSTATCTL);
	} while (!(done & ATOMICDONE));
	if (done & ATOMICERR)
		return -EFAULT;	  /* parity error */
	else if (done & ATOMICWIN)
		return 0;	  /* success */
	else
		return -EAGAIN;	  /* oldval different than current value */
}