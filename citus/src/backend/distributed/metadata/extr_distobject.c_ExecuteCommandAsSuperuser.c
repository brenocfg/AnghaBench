#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CitusExtensionOwner () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetUserIdAndSecContext (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int SECURITY_LOCAL_USERID_CHANGE ; 
 int SPI_OK_CONNECT ; 
 int SPI_OK_FINISH ; 
 int SPI_connect () ; 
 int SPI_execute_with_args (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int SPI_finish () ; 
 int /*<<< orphan*/  SetUserIdAndSecContext (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static int
ExecuteCommandAsSuperuser(char *query, int paramCount, Oid *paramTypes,
						  Datum *paramValues)
{
	int spiConnected = 0;
	Oid savedUserId = InvalidOid;
	int savedSecurityContext = 0;
	int spiStatus = 0;
	int spiFinished = 0;

	spiConnected = SPI_connect();
	if (spiConnected != SPI_OK_CONNECT)
	{
		ereport(ERROR, (errmsg("could not connect to SPI manager")));
	}

	/* make sure we have write access */
	GetUserIdAndSecContext(&savedUserId, &savedSecurityContext);
	SetUserIdAndSecContext(CitusExtensionOwner(), SECURITY_LOCAL_USERID_CHANGE);

	spiStatus = SPI_execute_with_args(query, paramCount, paramTypes, paramValues,
									  NULL, false, 0);

	SetUserIdAndSecContext(savedUserId, savedSecurityContext);

	spiFinished = SPI_finish();
	if (spiFinished != SPI_OK_FINISH)
	{
		ereport(ERROR, (errmsg("could not disconnect from SPI manager")));
	}

	return spiStatus;
}