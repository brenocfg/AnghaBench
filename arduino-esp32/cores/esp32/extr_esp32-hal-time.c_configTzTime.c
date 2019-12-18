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
 int /*<<< orphan*/  SNTP_OPMODE_POLL ; 
 int /*<<< orphan*/  setenv (char*,char const*,int) ; 
 scalar_t__ sntp_enabled () ; 
 int /*<<< orphan*/  sntp_init () ; 
 int /*<<< orphan*/  sntp_setoperatingmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sntp_setservername (int,char*) ; 
 int /*<<< orphan*/  sntp_stop () ; 
 int /*<<< orphan*/  tcpip_adapter_init () ; 
 int /*<<< orphan*/  tzset () ; 

void configTzTime(const char* tz, const char* server1, const char* server2, const char* server3)
{
    tcpip_adapter_init();  // Should not hurt anything if already inited
    if(sntp_enabled()){
        sntp_stop();
    }
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, (char*)server1);
    sntp_setservername(1, (char*)server2);
    sntp_setservername(2, (char*)server3);
    sntp_init();
    setenv("TZ", tz, 1);
    tzset();
}