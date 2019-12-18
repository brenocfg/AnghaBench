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
typedef  int UINT ;
typedef  void* UCHAR ;
struct TYPE_3__ {void* Id; void* Size; void* Data; } ;
typedef  TYPE_1__ DHCP_OPTION ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (void*,void*,int) ; 
 void* ZeroMalloc (int) ; 

DHCP_OPTION *NewDhcpOption(UINT id, void *data, UINT size)
{
	DHCP_OPTION *ret;
	if (size != 0 && data == NULL)
	{
		return NULL;
	}

	ret = ZeroMalloc(sizeof(DHCP_OPTION));
	ret->Data = ZeroMalloc(size);
	Copy(ret->Data, data, size);
	ret->Size = (UCHAR)size;
	ret->Id = (UCHAR)id;

	return ret;
}