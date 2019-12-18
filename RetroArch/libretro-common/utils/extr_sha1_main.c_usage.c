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
 int /*<<< orphan*/  printf (char*) ; 

void usage(void)
{
   printf("usage: sha <file> [<file> ...]\n");
   printf("\tThis program will display the message digest\n");
   printf("\tfor files using the Secure Hashing Algorithm (SHA-1).\n");
}