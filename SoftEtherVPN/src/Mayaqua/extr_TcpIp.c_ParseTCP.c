#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_4__ {int /*<<< orphan*/ * TCPHeader; } ;
struct TYPE_5__ {int PayloadSize; int /*<<< orphan*/ * Payload; int /*<<< orphan*/  TypeL4; TYPE_1__ L4; } ;
typedef  int /*<<< orphan*/  TCP_HEADER ;
typedef  TYPE_2__ PKT ;

/* Variables and functions */
 int /*<<< orphan*/  L4_TCP ; 
 int /*<<< orphan*/  L4_UNKNOWN ; 
 int TCP_GET_HEADER_SIZE (int /*<<< orphan*/ *) ; 

bool ParseTCP(PKT *p, UCHAR *buf, UINT size)
{
	UINT header_size;
	// Validate arguments
	if (p == NULL || buf == NULL)
	{
		return false;
	}

	// Check the size
	if (size < sizeof(TCP_HEADER))
	{
		// Size is invalid
		return false;
	}

	// TCP header
	p->L4.TCPHeader = (TCP_HEADER *)buf;
	p->TypeL4 = L4_TCP;

	// Check the header size
	header_size = TCP_GET_HEADER_SIZE(p->L4.TCPHeader) * 4;
	if (header_size < sizeof(TCP_HEADER) || size < header_size)
	{
		// Header size is invalid
		p->L4.TCPHeader = NULL;
		p->TypeL4 = L4_UNKNOWN;
		return true;
	}

	buf += header_size;
	size -= header_size;

	p->Payload = buf;
	p->PayloadSize = size;

	return true;
}