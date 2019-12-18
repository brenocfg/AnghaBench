#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int hdr_format; } ;
struct b43_wldev {TYPE_1__ fw; } ;
struct b43_plcp_hdr6 {int dummy; } ;

/* Variables and functions */
#define  B43_FW_HDR_351 130 
#define  B43_FW_HDR_410 129 
#define  B43_FW_HDR_598 128 

__attribute__((used)) static inline
size_t b43_txhdr_size(struct b43_wldev *dev)
{
	switch (dev->fw.hdr_format) {
	case B43_FW_HDR_598:
		return 112 + sizeof(struct b43_plcp_hdr6);
	case B43_FW_HDR_410:
		return 104 + sizeof(struct b43_plcp_hdr6);
	case B43_FW_HDR_351:
		return 100 + sizeof(struct b43_plcp_hdr6);
	}
	return 0;
}