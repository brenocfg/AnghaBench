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
struct sockaddr_in {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_family; } ;
struct in_addr {int dummy; } ;
struct hostent {scalar_t__ h_addr_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int ESP_FAIL ; 
 int ESP_OK ; 
 struct hostent* gethostbyname (char const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct in_addr*,int) ; 

__attribute__((used)) static int resolve_dns(const char *host, struct sockaddr_in *ip) {

    struct hostent *he;
    struct in_addr **addr_list;
    he = gethostbyname(host);
    if (he == NULL) {
        return ESP_FAIL;
    }
    addr_list = (struct in_addr **)he->h_addr_list;
    if (addr_list[0] == NULL) {
        return ESP_FAIL;
    }
    ip->sin_family = AF_INET;
    memcpy(&ip->sin_addr, addr_list[0], sizeof(ip->sin_addr));
    return ESP_OK;
}