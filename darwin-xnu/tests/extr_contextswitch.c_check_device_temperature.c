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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  POWERCTRL_SUCCESS_STR ; 
 int /*<<< orphan*/  T_END ; 
 int /*<<< orphan*/  T_FAIL (char*) ; 
 int /*<<< orphan*/  T_PASS (char*) ; 
 int /*<<< orphan*/  T_PERF (char*,double,char*,char*) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void check_device_temperature(void)
{
    char buffer[256];
    FILE *pipe = popen("powerctrl Factor1", "r");
    
    if (pipe == NULL) {
        T_FAIL("Failed to check device temperature");
        T_END;
    }

    fgets(buffer, sizeof(buffer), pipe);
    
    if (strncmp(POWERCTRL_SUCCESS_STR, buffer, strlen(POWERCTRL_SUCCESS_STR))) {
        T_PERF("temperature", 0.0, "factor", "device temperature");
    } else {
        T_PASS("Device temperature check pass");
        T_PERF("temperature", 1.0, "factor", "device temperature");
    }
    pclose(pipe);
}