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
 unsigned int scnprintf (char*,unsigned int,char*,char*,...) ; 

__attribute__((used)) static unsigned int gen_bitmask_string(int msk,int val,int msk_only,
				       const char **names,
				       char *ptr,unsigned int len)
{
	unsigned int idx;
	long sm,um;
	int spcFl;
	unsigned int uc,cnt;
	const char *idStr;

	spcFl = 0;
	uc = 0;
	um = 0;
	for (idx = 0, sm = 1; msk; idx++, sm <<= 1) {
		if (sm & msk) {
			msk &= ~sm;
			idStr = names[idx];
			if (idStr) {
				cnt = scnprintf(ptr,len,"%s%s%s",
						(spcFl ? " " : ""),
						(msk_only ? "" :
						 ((val & sm) ? "+" : "-")),
						idStr);
				ptr += cnt; len -= cnt; uc += cnt;
				spcFl = !0;
			} else {
				um |= sm;
			}
		}
	}
	if (um) {
		if (msk_only) {
			cnt = scnprintf(ptr,len,"%s0x%lx",
					(spcFl ? " " : ""),
					um);
			ptr += cnt; len -= cnt; uc += cnt;
			spcFl = !0;
		} else if (um & val) {
			cnt = scnprintf(ptr,len,"%s+0x%lx",
					(spcFl ? " " : ""),
					um & val);
			ptr += cnt; len -= cnt; uc += cnt;
			spcFl = !0;
		} else if (um & ~val) {
			cnt = scnprintf(ptr,len,"%s+0x%lx",
					(spcFl ? " " : ""),
					um & ~val);
			ptr += cnt; len -= cnt; uc += cnt;
			spcFl = !0;
		}
	}
	return uc;
}