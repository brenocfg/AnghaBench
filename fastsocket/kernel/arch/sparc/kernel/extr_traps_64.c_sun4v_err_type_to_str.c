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
typedef  int u32 ;

/* Variables and functions */
#define  SUN4V_ERR_TYPE_DEFERRED_NONRES 132 
#define  SUN4V_ERR_TYPE_PRECISE_NONRES 131 
#define  SUN4V_ERR_TYPE_UNCORRECTED_RES 130 
#define  SUN4V_ERR_TYPE_UNDEFINED 129 
#define  SUN4V_ERR_TYPE_WARNING_RES 128 

__attribute__((used)) static const char *sun4v_err_type_to_str(u32 type)
{
	switch (type) {
	case SUN4V_ERR_TYPE_UNDEFINED:
		return "undefined";
	case SUN4V_ERR_TYPE_UNCORRECTED_RES:
		return "uncorrected resumable";
	case SUN4V_ERR_TYPE_PRECISE_NONRES:
		return "precise nonresumable";
	case SUN4V_ERR_TYPE_DEFERRED_NONRES:
		return "deferred nonresumable";
	case SUN4V_ERR_TYPE_WARNING_RES:
		return "warning resumable";
	default:
		return "unknown";
	};
}