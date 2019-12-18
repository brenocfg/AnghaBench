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

/* Variables and functions */
 int SADB_X_SPDADD ; 
 int SADB_X_SPDDELETE ; 
 int SADB_X_SPDUPDATE ; 
#define  XFRM_MSG_DELPOLICY 131 
#define  XFRM_MSG_NEWPOLICY 130 
#define  XFRM_MSG_POLEXPIRE 129 
#define  XFRM_MSG_UPDPOLICY 128 
 int /*<<< orphan*/  printk (char*,int) ; 

__attribute__((used)) static inline int event2poltype(int event)
{
	switch (event) {
	case XFRM_MSG_DELPOLICY:
		return SADB_X_SPDDELETE;
	case XFRM_MSG_NEWPOLICY:
		return SADB_X_SPDADD;
	case XFRM_MSG_UPDPOLICY:
		return SADB_X_SPDUPDATE;
	case XFRM_MSG_POLEXPIRE:
	//	return SADB_X_SPDEXPIRE;
	default:
		printk("pfkey: Unknown policy event %d\n", event);
		break;
	}

	return 0;
}