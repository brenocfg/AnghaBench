#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int /*<<< orphan*/  UNICODE ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  scalar_t__ UINT ;
typedef  void* UCHAR ;
struct TYPE_11__ {int* MacAddress; int /*<<< orphan*/  HardwareID; int /*<<< orphan*/  HardwareID_Raw; int /*<<< orphan*/  NdisConfig; } ;
struct TYPE_10__ {int /*<<< orphan*/  Buffer; scalar_t__ MaximumLength; } ;
struct TYPE_8__ {int IntegerData; int /*<<< orphan*/  StringData; } ;
struct TYPE_9__ {scalar_t__ ParameterType; TYPE_1__ ParameterData; } ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;
typedef  int /*<<< orphan*/  NDIS_HANDLE ;
typedef  TYPE_2__ NDIS_CONFIGURATION_PARAMETER ;
typedef  int BOOL ;
typedef  TYPE_3__ ANSI_STRING ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  FreeUnicode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetUnicode (int /*<<< orphan*/ *) ; 
 scalar_t__ MAX_SIZE ; 
 scalar_t__ NEO_MAC_ADDRESS_SIZE ; 
 scalar_t__ NEO_MAX_SPEED_DEFAULT ; 
 scalar_t__ NG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisCloseConfiguration (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisOpenConfiguration (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ NdisParameterInteger ; 
 scalar_t__ NdisParameterString ; 
 int /*<<< orphan*/  NdisReadConfiguration (int /*<<< orphan*/ *,TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  NdisReadNetworkAddress (int /*<<< orphan*/ *,void**,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisUnicodeStringToAnsiString (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NeoCopy (int*,void*,scalar_t__) ; 
 int /*<<< orphan*/  NeoFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NeoZero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  NeoZeroMalloc (scalar_t__) ; 
 int /*<<< orphan*/ * NewUnicode (char*) ; 
 int TRUE ; 
 int /*<<< orphan*/  _strupr (int /*<<< orphan*/ ) ; 
 TYPE_4__* ctx ; 
 int keep_link ; 
 scalar_t__ max_speed ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL NeoLoadRegistry()
{
	void *buf;
	NDIS_STATUS ret;
	UINT size;
	NDIS_HANDLE config;
	NDIS_CONFIGURATION_PARAMETER *param;
	UNICODE *name;
	ANSI_STRING ansi;
	UNICODE_STRING *unicode;
	UINT speed;
	BOOL keep;

	// Get the config handle
	NdisOpenConfiguration(&ret, &config, ctx->NdisConfig);
	if (NG(ret))
	{
		// Failure
		return FALSE;
	}

	// Read the MAC address
	NdisReadNetworkAddress(&ret, &buf, &size, config);
	if (NG(ret))
	{
		// Failure
		NdisCloseConfiguration(config);
		return FALSE;
	}

	// Copy the MAC address
	if (size != NEO_MAC_ADDRESS_SIZE)
	{
		// Invalid size
		NdisCloseConfiguration(config);
		return FALSE;
	}
	NeoCopy(ctx->MacAddress, buf, NEO_MAC_ADDRESS_SIZE);

	if (ctx->MacAddress[0] == 0x00 &&
		ctx->MacAddress[1] == 0x00 &&
		ctx->MacAddress[2] == 0x01 &&
		ctx->MacAddress[3] == 0x00 &&
		ctx->MacAddress[4] == 0x00 &&
		ctx->MacAddress[5] == 0x01)
	{
		// Special MAC address
		UINT ptr32 = (UINT)((UINT64)ctx);

		ctx->MacAddress[0] = 0x00;
		ctx->MacAddress[1] = 0xAD;
		ctx->MacAddress[2] = ((UCHAR *)(&ptr32))[0];
		ctx->MacAddress[3] = ((UCHAR *)(&ptr32))[1];
		ctx->MacAddress[4] = ((UCHAR *)(&ptr32))[2];
		ctx->MacAddress[5] = ((UCHAR *)(&ptr32))[3];
	}

	// Initialize the key name of the device name
	name = NewUnicode("MatchingDeviceId");

	// Read the hardware ID
	NdisReadConfiguration(&ret, &param, config, GetUnicode(name), NdisParameterString);
	FreeUnicode(name);
	if (NG(ret))
	{
		// Failure
		NdisCloseConfiguration(config);
		return FALSE;
	}
	// Type checking
	if (param->ParameterType != NdisParameterString)
	{
		// Failure
		NdisCloseConfiguration(config);
		return FALSE;
	}
	unicode = &param->ParameterData.StringData;

	// Prepare a buffer for ANSI string
	NeoZero(&ansi, sizeof(ANSI_STRING));
	ansi.MaximumLength = MAX_SIZE - 1;
	ansi.Buffer = NeoZeroMalloc(MAX_SIZE);

	// Convert to ANSI string
	NdisUnicodeStringToAnsiString(&ansi, unicode);
	// Copy
	strcpy(ctx->HardwareID, ansi.Buffer);
	strcpy(ctx->HardwareID_Raw, ctx->HardwareID);
	// Convert to upper case
	_strupr(ctx->HardwareID);
	// Release the memory
	NeoFree(ansi.Buffer);

	// Read the bit rate
	name = NewUnicode("MaxSpeed");
	NdisReadConfiguration(&ret, &param, config, GetUnicode(name), NdisParameterInteger);
	FreeUnicode(name);

	if (NG(ret) || param->ParameterType != NdisParameterInteger)
	{
		speed = NEO_MAX_SPEED_DEFAULT;
	}
	else
	{
		speed = param->ParameterData.IntegerData * 10000;
	}

	max_speed = speed;

	// Read the link keeping flag
	name = NewUnicode("KeepLink");
	NdisReadConfiguration(&ret, &param, config, GetUnicode(name), NdisParameterInteger);
	FreeUnicode(name);

	if (NG(ret) || param->ParameterType != NdisParameterInteger)
	{
		keep = false;
	}
	else
	{
		keep = (param->ParameterData.IntegerData == 0 ? false : true);
	}

	keep_link = keep;

	// Close the Config handle
	NdisCloseConfiguration(config);

	return TRUE;
}