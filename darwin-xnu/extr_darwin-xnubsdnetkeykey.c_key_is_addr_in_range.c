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
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct secpolicyaddrrange {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int key_sockaddrcmp (struct sockaddr*,struct sockaddr*,int) ; 

__attribute__((used)) static int
key_is_addr_in_range(struct sockaddr_storage *addr, struct secpolicyaddrrange *addr_range)
{
    int cmp = 0;
    
    if (addr == NULL || addr_range == NULL)
        return 0;
    
    /* Must be greater than or equal to start */
    cmp = key_sockaddrcmp((struct sockaddr *)addr, (struct sockaddr *)&addr_range->start, 1);
    if (cmp != 0 && cmp != 1)
        return 0;
	
    /* Must be less than or equal to end */
    cmp = key_sockaddrcmp((struct sockaddr *)addr, (struct sockaddr *)&addr_range->end, 1);
    if (cmp != 0 && cmp != -1)
        return 0;
	
    return 1;
}