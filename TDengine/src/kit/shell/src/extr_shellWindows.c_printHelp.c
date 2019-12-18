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
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void printHelp() {
  char indent[10] = "        ";
  printf("taos shell is used to test the TDEngine database\n");

  printf("%s%s\n", indent, "-h");
  printf("%s%s%s\n", indent, indent, "TDEngine server IP address to connect. The default host is localhost.");
  printf("%s%s\n", indent, "-p");
  printf("%s%s%s\n", indent, indent, "The password to use when connecting to the server.");
  printf("%s%s\n", indent, "-P");
  printf("%s%s%s\n", indent, indent, "The TCP/IP port number to use for the connection");
  printf("%s%s\n", indent, "-u");
  printf("%s%s%s\n", indent, indent, "The TDEngine user name to use when connecting to the server.");
  printf("%s%s\n", indent, "-c");
  printf("%s%s%s\n", indent, indent, "Configuration directory.");
  printf("%s%s\n", indent, "-s");
  printf("%s%s%s\n", indent, indent, "Commands to run without enter the shell.");
  printf("%s%s\n", indent, "-r");
  printf("%s%s%s\n", indent, indent, "Output time as unsigned long..");
  printf("%s%s\n", indent, "-f");
  printf("%s%s%s\n", indent, indent, "Script to run without enter the shell.");
  printf("%s%s\n", indent, "-d");
  printf("%s%s%s\n", indent, indent, "Database to use when connecting to the server.");
  printf("%s%s\n", indent, "-t");
  printf("%s%s%s\n", indent, indent, "Time zone of the shell, default is local.");

  exit(EXIT_SUCCESS);
}