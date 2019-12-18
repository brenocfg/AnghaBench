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
struct TYPE_4__ {int IsControl; int /*<<< orphan*/  DataSize; int /*<<< orphan*/  Data; } ;
typedef  TYPE_1__ SSTP_PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  Clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* ZeroMalloc (int) ; 

SSTP_PACKET *SstpNewDataPacket(UCHAR *data, UINT size)
{
	SSTP_PACKET *p = ZeroMalloc(sizeof(SSTP_PACKET));

	p->IsControl = false;
	p->Data = Clone(data, size);
	p->DataSize = size;

	return p;
}