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
struct ks8695_priv {int dtype; } ;

/* Variables and functions */
#define  KS8695_DTYPE_HPNA 130 
#define  KS8695_DTYPE_LAN 129 
#define  KS8695_DTYPE_WAN 128 

__attribute__((used)) static const char *
ks8695_port_type(struct ks8695_priv *ksp)
{
	switch (ksp->dtype) {
	case KS8695_DTYPE_LAN:
		return "LAN";
	case KS8695_DTYPE_WAN:
		return "WAN";
	case KS8695_DTYPE_HPNA:
		return "HPNA";
	}

	return "UNKNOWN";
}