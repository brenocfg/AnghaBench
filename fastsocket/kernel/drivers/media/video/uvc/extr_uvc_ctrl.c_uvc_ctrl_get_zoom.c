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
struct uvc_control_mapping {int dummy; } ;
typedef  int __u8 ;
typedef  int /*<<< orphan*/  __s8 ;
typedef  int const __s32 ;

/* Variables and functions */
#define  UVC_GET_CUR 132 
#define  UVC_GET_DEF 131 
#define  UVC_GET_MAX 130 
#define  UVC_GET_MIN 129 
#define  UVC_GET_RES 128 

__attribute__((used)) static __s32 uvc_ctrl_get_zoom(struct uvc_control_mapping *mapping,
	__u8 query, const __u8 *data)
{
	__s8 zoom = (__s8)data[0];

	switch (query) {
	case UVC_GET_CUR:
		return (zoom == 0) ? 0 : (zoom > 0 ? data[2] : -data[2]);

	case UVC_GET_MIN:
	case UVC_GET_MAX:
	case UVC_GET_RES:
	case UVC_GET_DEF:
	default:
		return data[2];
	}
}