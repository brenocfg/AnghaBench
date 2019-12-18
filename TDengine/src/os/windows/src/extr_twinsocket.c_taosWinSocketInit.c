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
typedef  int /*<<< orphan*/  WSADATA ;
typedef  int /*<<< orphan*/  WORD ;

/* Variables and functions */
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 scalar_t__ WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void taosWinSocketInit() {
    static char flag = 0;
    if (flag == 0) {
        WORD wVersionRequested;
        WSADATA wsaData;
        wVersionRequested = MAKEWORD(1, 1);
        if (WSAStartup(wVersionRequested, &wsaData) == 0) {
            flag = 1;
        }
    }
}