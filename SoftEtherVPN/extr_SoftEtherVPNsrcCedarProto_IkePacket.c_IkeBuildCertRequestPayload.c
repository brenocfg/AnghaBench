#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h ;
struct TYPE_7__ {int /*<<< orphan*/  CertType; } ;
struct TYPE_6__ {int /*<<< orphan*/  Data; int /*<<< orphan*/  CertType; } ;
typedef  TYPE_1__ IKE_PACKET_CERT_REQUEST_PAYLOAD ;
typedef  TYPE_2__ IKE_CERT_REQUEST_HEADER ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  WriteBufBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

BUF *IkeBuildCertRequestPayload(IKE_PACKET_CERT_REQUEST_PAYLOAD *t)
{
	IKE_CERT_REQUEST_HEADER h;
	BUF *ret;
	// Validate arguments
	if (t == NULL)
	{
		return NULL;
	}

	Zero(&h, sizeof(h));
	h.CertType = t->CertType;

	ret = NewBuf();
	WriteBuf(ret, &h, sizeof(h));
	WriteBufBuf(ret, t->Data);

	return ret;
}