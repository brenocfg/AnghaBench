#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sni ;
typedef  int /*<<< orphan*/  h ;
struct TYPE_13__ {int IsSsl; int /*<<< orphan*/  Path; int /*<<< orphan*/  Port; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  Method; } ;
struct TYPE_11__ {TYPE_1__* TCPHeader; } ;
struct TYPE_12__ {TYPE_2__ L4; int /*<<< orphan*/  PayloadSize; int /*<<< orphan*/  Payload; } ;
struct TYPE_10__ {int /*<<< orphan*/  DstPort; } ;
typedef  TYPE_3__ PKT ;
typedef  TYPE_4__ HTTPLOG ;

/* Variables and functions */
 TYPE_4__* Clone (TYPE_4__*,int) ; 
 int /*<<< orphan*/  Endian16 (int /*<<< orphan*/ ) ; 
 int GetSniNameFromSslPacket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_4__*,int) ; 

HTTPLOG *ParseHttpsAccessLog(PKT *pkt)
{
	HTTPLOG h;
	char sni[MAX_PATH];
	// Validate arguments
	if (pkt == NULL)
	{
		return NULL;
	}

	if (GetSniNameFromSslPacket(pkt->Payload, pkt->PayloadSize, sni, sizeof(sni)) == false)
	{
		return NULL;
	}

	Zero(&h, sizeof(h));

	StrCpy(h.Method, sizeof(h.Method), "SSL_Connect");
	StrCpy(h.Hostname, sizeof(h.Hostname), sni);
	h.Port = Endian16(pkt->L4.TCPHeader->DstPort);
	StrCpy(h.Path, sizeof(h.Path), "/");
	h.IsSsl = true;

	return Clone(&h, sizeof(h));
}