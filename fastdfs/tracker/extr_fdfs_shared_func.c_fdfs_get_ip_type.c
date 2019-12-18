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
 int FDFS_IP_TYPE_OUTER ; 
 int FDFS_IP_TYPE_PRIVATE_10 ; 
 int FDFS_IP_TYPE_PRIVATE_172 ; 
 int FDFS_IP_TYPE_PRIVATE_192 ; 
 int FDFS_IP_TYPE_UNKNOWN ; 
 int atoi (char const*) ; 
 scalar_t__ memcmp (char const*,char*,int) ; 
 scalar_t__ strlen (char const*) ; 

int fdfs_get_ip_type(const char* ip)
{
    if (ip == NULL || (int)strlen(ip) < 8)
    {
        return FDFS_IP_TYPE_UNKNOWN;
    }

    if (memcmp(ip, "10.", 3) == 0)
    {
        return FDFS_IP_TYPE_PRIVATE_10;
    }
    if (memcmp(ip, "192.168.", 8) == 0)
    {
        return FDFS_IP_TYPE_PRIVATE_192;
    }

    if (memcmp(ip, "172.", 4) == 0)
    {
        int b;
        b = atoi(ip + 4);
        if (b >= 16 && b < 32)
        {
            return FDFS_IP_TYPE_PRIVATE_172;
        }
    }

    return FDFS_IP_TYPE_OUTER;
}