#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {double width; double height; } ;
typedef  TYPE_1__ ccv_size_t ;
struct TYPE_8__ {double x; double y; } ;
typedef  TYPE_2__ ccv_decimal_point_t ;

/* Variables and functions */
 TYPE_2__ ccv_decimal_point (float,float) ; 
 double ccv_max (double,double) ; 

ccv_decimal_point_t ccv_perspective_transform_apply(ccv_decimal_point_t point, ccv_size_t size, float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22)
{
	m00 *= 1.0 / ccv_max(size.width, size.height);
	m01 *= 1.0 / ccv_max(size.width, size.height);
	m02 *= 1.0 / ccv_max(size.width, size.height);
	m10 *= 1.0 / ccv_max(size.width, size.height);
	m11 *= 1.0 / ccv_max(size.width, size.height);
	m12 *= 1.0 / ccv_max(size.width, size.height);
	m20 *= 1.0 / (ccv_max(size.width, size.height) * ccv_max(size.width, size.height));
	m21 *= 1.0 / (ccv_max(size.width, size.height) * ccv_max(size.width, size.height));
	m22 *= 1.0 / ccv_max(size.width, size.height);
	point.x -= size.width * 0.5;
	point.y -= size.height * 0.5;
	float wz = 1.0 / (point.x * m20 + point.y * m21 + m22);
	float wx = size.width * 0.5 + (point.x * m00 + point.y * m01 + m02) * wz;
	float wy = size.height * 0.5 + (point.x * m10 + point.y * m11 + m12) * wz;
	return ccv_decimal_point(wx, wy);
}