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
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  dst ;

/* Variables and functions */
 int PROXY_TO_PTHREAD ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  getDomElementInnerHTML (char*,char*,int) ; 
 int isThisInWorker () ; 
 int isThisInWorkerOnMainThread () ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int) ; 
 int receivesAndReturnsAnInteger (int) ; 
 int /*<<< orphan*/  strstr (char*,char*) ; 

int main()
{
	char dst[256];
	char name[7] = "resize";
	getDomElementInnerHTML(name, dst, sizeof(dst));
	memset(name, 0, sizeof(name)); // Try to uncover if there might be a race condition and above line was not synchronously processed, and we could take name string away.
	int inWorker1 = isThisInWorker(); // Build this application with -s USE_PTHREADS=1 -s PROXY_TO_PTHREAD=1 for this to return 1, otherwise returns 0.
	int inWorker2 = isThisInWorkerOnMainThread(); // This should always return 0
	int returnedInt = receivesAndReturnsAnInteger(4);
	printf("text: \"%s\". inWorker1: %d, inWorker2: %d, returnedInt: %d\n", dst, inWorker1, inWorker2, returnedInt);
	assert(!strstr(dst, "Resize canvas"));
	assert(inWorker1 == PROXY_TO_PTHREAD);
	assert(inWorker2 == 0);
	assert(returnedInt == 42 + 4);
#ifdef REPORT_RESULT
	REPORT_RESULT(1);
#endif
}