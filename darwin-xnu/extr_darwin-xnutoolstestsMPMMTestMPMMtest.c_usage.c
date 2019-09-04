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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

void usage(const char *progname) {
	fprintf(stderr, "usage: %s [options]\n", progname);
	fprintf(stderr, "where options are:\n");
	fprintf(stderr, "    -affinity\t\tthreads use affinity\n");
	fprintf(stderr, "    -timeshare\t\tthreads use timeshare\n");
	fprintf(stderr, "    -threaded\t\tuse (p)threads\n");
	fprintf(stderr, "    -verbose\t\tbe verbose (use multiple times to increase verbosity)\n");
	fprintf(stderr, "    -oneway\t\tdo not request return reply\n");
	fprintf(stderr, "    -count num\t\tnumber of messages to send\n");
	fprintf(stderr, "    -perf   \t\tCreate perfdata files for metrics.\n");
	fprintf(stderr, "    -type trivial|inline|complex\ttype of messages to send\n");
	fprintf(stderr, "    -numints num\tnumber of 32-bit ints to send in messages\n");
	fprintf(stderr, "    -servers num\tnumber of server threads to run\n");
	fprintf(stderr, "    -clients num\tnumber of clients per server\n");
	fprintf(stderr, "    -delay num\t\tmicroseconds to sleep clients between messages\n");
	fprintf(stderr, "    -work num\t\tmicroseconds of client work\n");
	fprintf(stderr, "    -pages num\t\tpages of memory touched by client work\n");
	fprintf(stderr, "    -set nset num\tcreate [nset] portsets and [num] ports in each server.\n");
	fprintf(stderr, "                 \tEach port is connected to each set.\n");
	fprintf(stderr, "    -prepost\t\tstress the prepost system (implies -threaded, requires -set X Y)\n");
	fprintf(stderr, "default values are:\n");
	fprintf(stderr, "    . no affinity\n");
	fprintf(stderr, "    . not timeshare\n");
	fprintf(stderr, "    . not threaded\n");
	fprintf(stderr, "    . not verbose\n");
	fprintf(stderr, "    . not oneway\n");
	fprintf(stderr, "    . client sends 100000 messages\n");
	fprintf(stderr, "    . inline message type\n");
	fprintf(stderr, "    . 64 32-bit integers in inline/complex messages\n");
	fprintf(stderr, "    . (num_available_processors+1)%%2 servers\n");
	fprintf(stderr, "    . 4 clients per server\n");
	fprintf(stderr, "    . no delay\n");
	fprintf(stderr, "    . no sets / extra ports\n");
	fprintf(stderr, "    . no prepost stress\n");
	exit(1);
}