#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  taskname ;
struct TYPE_6__ {int IsConnected; TYPE_1__* Server; } ;
struct TYPE_5__ {int /*<<< orphan*/  TasksFromFarmControllerLock; } ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_2__ FARM_CONTROLLER ;

/* Variables and functions */
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HttpClientRecv (int /*<<< orphan*/ *) ; 
 int HttpClientSend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ PackGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/ * SiCalledTask (TYPE_2__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

void SiAcceptTasksFromControllerMain(FARM_CONTROLLER *f, SOCK *sock)
{
	PACK *request;
	PACK *response;
	char taskname[MAX_SIZE];
	// Validate arguments
	if (f == NULL || sock == NULL)
	{
		return;
	}

	f->IsConnected = true;

	while (true)
	{
		bool ret;
		// Receive the PACK
		request = HttpClientRecv(sock);
		if (request == NULL)
		{
			// Disconnect
			break;
		}

		response = NULL;

		// Get the name
		if (PackGetStr(request, "taskname", taskname, sizeof(taskname)))
		{
			Lock(f->Server->TasksFromFarmControllerLock);
			{
				response = SiCalledTask(f, request, taskname);
			}
			Unlock(f->Server->TasksFromFarmControllerLock);
		}

		FreePack(request);

		// Return a response
		if (response == NULL)
		{
			response = NewPack();
		}
		else
		{
			PackAddInt(response, "succeed", 1);
		}

		ret = HttpClientSend(sock, response);
		FreePack(response);

		if (ret == false)
		{
			// Disconnect
			break;
		}
	}

	f->IsConnected = false;
}