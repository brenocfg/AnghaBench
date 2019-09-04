#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  Value; int /*<<< orphan*/  Type; } ;
typedef  TYPE_1__ IKE_PACKET_TRANSFORM_VALUE ;

/* Variables and functions */
 TYPE_1__* ZeroMalloc (int) ; 

IKE_PACKET_TRANSFORM_VALUE *IkeNewTransformValue(UCHAR type, UINT value)
{
	IKE_PACKET_TRANSFORM_VALUE *v = ZeroMalloc(sizeof(IKE_PACKET_TRANSFORM_VALUE));

	v->Type = type;
	v->Value = value;

	return v;
}