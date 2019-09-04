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
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  MsChapV2_ClientResponse; int /*<<< orphan*/  MsChapV2_PPPUsername; int /*<<< orphan*/  MsChapV2_ServerChallenge; int /*<<< orphan*/  MsChapV2_ClientChallenge; } ;
typedef  TYPE_1__ IPC_MSCHAP_V2_AUTHINFO ;

/* Variables and functions */
 scalar_t__ Cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GenerateNtPasswordHash (int /*<<< orphan*/ *,char*) ; 
 int MD5_SIZE ; 
 int /*<<< orphan*/  MsChapV2Client_GenerateResponse (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MsChapV2_GenerateChallenge8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool MsChapV2VerityPassword(IPC_MSCHAP_V2_AUTHINFO *d, char *password)
{
	UCHAR ntlm_hash[MD5_SIZE];
	UCHAR challenge8[8];
	UCHAR client_response[24];
	// Validate arguments
	if (d == NULL || password == NULL)
	{
		return false;
	}

	GenerateNtPasswordHash(ntlm_hash, password);
	MsChapV2_GenerateChallenge8(challenge8, d->MsChapV2_ClientChallenge, d->MsChapV2_ServerChallenge, d->MsChapV2_PPPUsername);
	MsChapV2Client_GenerateResponse(client_response, challenge8, ntlm_hash);

	if (Cmp(client_response, d->MsChapV2_ClientResponse, 24) != 0)
	{
		return false;
	}

	return true;
}