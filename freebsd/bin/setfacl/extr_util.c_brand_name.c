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
#define  ACL_BRAND_NFS4 129 
#define  ACL_BRAND_POSIX 128 

const char *
brand_name(int brand)
{
	switch (brand) {
	case ACL_BRAND_NFS4:
		return "NFSv4";
	case ACL_BRAND_POSIX:
		return "POSIX.1e";
	default:
		return "unknown";
	}
}