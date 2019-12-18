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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	fprintf(stderr, "usage: brssl command [ options ]\n");
	fprintf(stderr, "available commands:\n");
	fprintf(stderr, "   client       run SSL client\n");
	fprintf(stderr, "   server       run SSL server\n");
	fprintf(stderr, "   verify       verify certificate chain\n");
	fprintf(stderr, "   skey         decode private key\n");
	fprintf(stderr, "   ta           decode trust anchors\n");
	fprintf(stderr, "   chain        make C code for certificate chains\n");
	fprintf(stderr, "   twrch        run the Twrch protocol\n");
	fprintf(stderr, "   impl         report on implementations\n");
}