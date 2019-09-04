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
struct in_addr {int dummy; } ;
struct sockaddr_in {struct in_addr sin_addr; } ;
struct addrinfo {scalar_t__ ai_family; scalar_t__ ai_addr; struct addrinfo* ai_next; } ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 scalar_t__ getaddrinfo (char const*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  inet_aton (char const*,struct in_addr*) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 

int resolve_host(struct in_addr *sin_addr, const char *hostname) 
{ 
    if (!inet_aton(hostname, sin_addr)) { 
        struct addrinfo *ai, *cur; 
        struct addrinfo hints; 
        memset(&hints, 0, sizeof(hints)); 
        hints.ai_family = AF_INET; 
        if (getaddrinfo(hostname, NULL, &hints, &ai)) 
            return -1; 
        for (cur = ai; cur; cur = cur->ai_next) { 
            if (cur->ai_family == AF_INET) { 
                *sin_addr = ((struct sockaddr_in *)cur->ai_addr)->sin_addr; 
                freeaddrinfo(ai); 
                return 0; 
            } 
        } 
        freeaddrinfo(ai); 
        return -1; 
    } 
    return 0; 
}