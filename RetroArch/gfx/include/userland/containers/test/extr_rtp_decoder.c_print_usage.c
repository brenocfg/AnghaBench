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
 int /*<<< orphan*/  LOG_INFO (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void print_usage(char *program_name)
{
   LOG_INFO(NULL, "Usage:");
   LOG_INFO(NULL, "  %s [opts] <uri>", program_name);
   LOG_INFO(NULL, "Reads RTP packets from <uri>, decodes to standard output.");
   LOG_INFO(NULL, "Press the escape key to terminate the program.");
   LOG_INFO(NULL, "Options:");
   LOG_INFO(NULL, "  -h   Print this information");
   LOG_INFO(NULL, "  -s x Save packets to URI x");
   LOG_INFO(NULL, "  -v   Dump standard packet header");
   LOG_INFO(NULL, "  -vv  Dump entire header");
   LOG_INFO(NULL, "  -vvv Dump entire header and data");
}