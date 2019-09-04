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
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  USHORT ;
typedef  size_t UINT ;
typedef  int UCHAR ;
struct TYPE_4__ {int WindowScaling; int /*<<< orphan*/  MaxSegmentSize; } ;
typedef  TYPE_1__ TCP_OPTION ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int*,int*,size_t) ; 
 int /*<<< orphan*/  Endian16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void ParseTcpOption(TCP_OPTION *o, void *data, UINT size)
{
	UCHAR *buf = (UCHAR *)data;
	UINT i = 0;
	UINT value_size = 0;
	UINT value_id = 0;
	UCHAR value[128];
	// Validate arguments
	if (o == NULL || data == NULL)
	{
		return;
	}

	Zero(o, sizeof(TCP_OPTION));

	while(i < size)
	{
		if (buf[i] == 0)
		{
			return;
		}
		else if (buf[i] == 1)
		{
			i++;
			continue;
		}
		else
		{
			value_id = buf[i];
			i++;
			if (i >= size)
			{
				return;
			}
			value_size = buf[i];
			if (value_size <= 1 || value_size > sizeof(value))
			{
				return;
			}
			i++;
			if (i >= size)
			{
				return;
			}
			value_size -= 2;
                   
			Copy(value, &buf[i], value_size);
			i += value_size;
			if (i > size)
			{
				return;
			}

			switch (value_id)
			{
			case 2:	// MSS
				if (value_size == 2)
				{
					USHORT *mss = (USHORT *)value;
					o->MaxSegmentSize = Endian16(*mss);
				}
				break;

			case 3: // WSS
				if (value_size == 1)
				{
					UCHAR *wss = (UCHAR *)value;
					o->WindowScaling = *wss;
				}
				break;

			}
		}
	}
}