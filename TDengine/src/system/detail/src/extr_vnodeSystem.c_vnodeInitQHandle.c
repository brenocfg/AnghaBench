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

/* Variables and functions */
 void* dmQhandle ; 
 void** malloc (int) ; 
 void** rpcQhandle ; 
 void* taosInitScheduler (int /*<<< orphan*/ ,int,char*) ; 
 int tsMaxQueues ; 
 double tsNumOfCores ; 
 double tsNumOfThreadsPerCore ; 
 double tsRatioOfQueryThreads ; 
 int /*<<< orphan*/  tsSessionsPerVnode ; 

void vnodeInitQHandle() {
  tsMaxQueues = (1.0 - tsRatioOfQueryThreads)*tsNumOfCores*tsNumOfThreadsPerCore / 2.0;
  if (tsMaxQueues < 1) tsMaxQueues = 1;

  rpcQhandle = malloc(tsMaxQueues*sizeof(void *));

  for (int i=0; i< tsMaxQueues; ++i ) 
    rpcQhandle[i] = taosInitScheduler(tsSessionsPerVnode, 1, "dnode");

  dmQhandle = taosInitScheduler(tsSessionsPerVnode, 1, "mgmt");
}