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
 int /*<<< orphan*/  client_enabled ; 
 int client_sendall (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  sd ; 
 int /*<<< orphan*/  strlen (char*) ; 

void client_send(char *data) {
    if (!client_enabled) {
        return;
    }
    if (client_sendall(sd, data, strlen(data)) == -1) {
        perror("client_sendall");
        exit(1);
    }
}