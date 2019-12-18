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
 int bytes_sent ; 
 int /*<<< orphan*/  client_enabled ; 
 int send (int,char*,int,int /*<<< orphan*/ ) ; 

int client_sendall(int sd, char *data, int length) {
    if (!client_enabled) {
        return 0;
    }
    int count = 0;
    while (count < length) {
        int n = send(sd, data + count, length, 0);
        if (n == -1) {
            return -1;
        }
        count += n;
        length -= n;
        bytes_sent += n;
    }
    return 0;
}