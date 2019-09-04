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
typedef  int uint8_t ;
struct in_addr {unsigned int s_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,int) ; 

char* inet_ntoa( struct in_addr in ) {
    unsigned int ip;
    static char __inet_ntoa_result[18];
    int i;
    uint8_t bytes[4];
    uint8_t* addrbyte;

    ip = in.s_addr;

    addrbyte = (uint8_t *)&ip;

    for(i = 0; i < 4; i++) {
        bytes[i] = *addrbyte++;
    }

    snprintf (__inet_ntoa_result, 18, "%d.%d.%d.%d", bytes[0], bytes[1], bytes[2], bytes[3]);

    return __inet_ntoa_result;
}