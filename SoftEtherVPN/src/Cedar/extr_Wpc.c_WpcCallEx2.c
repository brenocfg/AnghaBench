#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X ;
struct TYPE_13__ {int /*<<< orphan*/ * Pack; int /*<<< orphan*/  Cert; } ;
typedef  TYPE_1__ WPC_PACKET ;
struct TYPE_14__ {int /*<<< orphan*/  SniString; int /*<<< orphan*/  AdditionalHeaderValue; int /*<<< orphan*/  AdditionalHeaderName; } ;
typedef  TYPE_2__ URL_DATA ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_15__ {int /*<<< orphan*/  Buf; int /*<<< orphan*/  Size; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  K ;
typedef  int /*<<< orphan*/  INTERNET_SETTING ;
typedef  TYPE_3__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_PROTOCOL_ERROR ; 
 int /*<<< orphan*/  FreeBuf (TYPE_3__*) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ ) ; 
 TYPE_3__* HttpRequestEx3 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IsEmptyStr (char*) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * PackError (int /*<<< orphan*/ ) ; 
 int ParseUrl (TYPE_2__*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SeekBuf (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 TYPE_3__* WpcGeneratePacket (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int WpcParsePacket (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  WriteBufInt (TYPE_3__*,int /*<<< orphan*/ ) ; 

PACK *WpcCallEx2(char *url, INTERNET_SETTING *setting, UINT timeout_connect, UINT timeout_comm,
				char *function_name, PACK *pack, X *cert, K *key, void *sha1_cert_hash, UINT num_hashes, bool *cancel, UINT max_recv_size,
				char *additional_header_name, char *additional_header_value, char *sni_string)
{
	URL_DATA data;
	BUF *b, *recv;
	UINT error;
	WPC_PACKET packet;
	// Validate arguments
	if (function_name == NULL || pack == NULL)
	{
		return PackError(ERR_INTERNAL_ERROR);
	}

	if (ParseUrl(&data, url, true, NULL) == false)
	{
		return PackError(ERR_INTERNAL_ERROR);
	}

	PackAddStr(pack, "function", function_name);

	b = WpcGeneratePacket(pack, cert, key);
	if (b == NULL)
	{
		return PackError(ERR_INTERNAL_ERROR);
	}

	SeekBuf(b, b->Size, 0);
	WriteBufInt(b, 0);
	SeekBuf(b, 0, 0);

	if (IsEmptyStr(additional_header_name) == false && IsEmptyStr(additional_header_value) == false)
	{
		StrCpy(data.AdditionalHeaderName, sizeof(data.AdditionalHeaderName), additional_header_name);
		StrCpy(data.AdditionalHeaderValue, sizeof(data.AdditionalHeaderValue), additional_header_value);
	}

	if (sni_string != NULL && IsEmptyStr(sni_string) == false)
	{
		StrCpy(data.SniString, sizeof(data.SniString), sni_string);
	}

	recv = HttpRequestEx3(&data, setting, timeout_connect, timeout_comm, &error,
		false, b->Buf, NULL, NULL, sha1_cert_hash, num_hashes, cancel, max_recv_size,
		NULL, NULL);

	FreeBuf(b);

	if (recv == NULL)
	{
		return PackError(error);
	}

	if (WpcParsePacket(&packet, recv) == false)
	{
		FreeBuf(recv);
		return PackError(ERR_PROTOCOL_ERROR);
	}

	FreeBuf(recv);

	FreeX(packet.Cert);

	return packet.Pack;
}