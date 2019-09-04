#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  type ;
typedef  int /*<<< orphan*/  size_or_value ;
typedef  int /*<<< orphan*/  af_bit ;
typedef  int USHORT ;
typedef  int UINT ;
typedef  int UCHAR ;
struct TYPE_3__ {int Type; int Value; } ;
typedef  TYPE_1__ IKE_PACKET_TRANSFORM_VALUE ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int Endian16 (int) ; 
 int Endian32 (int) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,int*,int) ; 

BUF *IkeBuildTransformValue(IKE_PACKET_TRANSFORM_VALUE *v)
{
	BUF *b;
	UCHAR af_bit, type;
	USHORT size_or_value;
	// Validate arguments
	if (v == NULL)
	{
		return NULL;
	}

	type = v->Type;

	if (v->Value >= 65536)
	{
		// 32 bit
		af_bit = 0;
		size_or_value = Endian16(sizeof(UINT));
	}
	else
	{
		// 16 bit
		af_bit = 0x80;
		size_or_value = Endian16((USHORT)v->Value);
	}

	b = NewBuf();
	WriteBuf(b, &af_bit, sizeof(af_bit));
	WriteBuf(b, &type, sizeof(type));
	WriteBuf(b, &size_or_value, sizeof(size_or_value));

	if (af_bit == 0)
	{
		UINT value = Endian32(v->Value);
		WriteBuf(b, &value, sizeof(UINT));
	}

	return b;
}