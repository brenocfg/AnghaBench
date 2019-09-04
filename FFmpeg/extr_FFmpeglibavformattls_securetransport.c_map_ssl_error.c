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
typedef  int OSStatus ;

/* Variables and functions */
#define  errSSLClosedGraceful 131 
#define  errSSLClosedNoNotify 130 
#define  errSSLWouldBlock 129 
#define  noErr 128 

__attribute__((used)) static int map_ssl_error(OSStatus status, size_t processed)
{
    switch (status) {
    case noErr:
        return processed;
    case errSSLClosedGraceful:
    case errSSLClosedNoNotify:
        return 0;
    case errSSLWouldBlock:
        if (processed > 0)
            return processed;
    default:
        return (int)status;
    }
}