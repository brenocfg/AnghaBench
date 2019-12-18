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
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  sleep (int) ; 

int main(int argc, char **args)
{
    printf("REPORT %s:%s\n", "127.0.0.1", "80");

    while (1)
        sleep(1);

    return 0;
}